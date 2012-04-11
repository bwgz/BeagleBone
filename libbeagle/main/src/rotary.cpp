/*
 * Copyright (c) 2012 bwgz.org
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <rotary.h>

Rotary::Rotary() : _position(0) {
}

Rotary::Rotary(unsigned a, unsigned b) : _position(0) {
	A = new GPIO(a);
	B = new GPIO(b);

	A->direction("in");
	B->direction("in");
}

Rotary::~Rotary() {
	if (A != NULL) {
		delete A;
	}
	if (B != NULL) {
		delete B;
	}
}

unsigned Rotary::phase() {
	unsigned a = A->value();
	unsigned b = B->value();

	a = (a == 0) ? 1 : 0;
	b = (b == 0) ? 1 : 0;

	return (a << 1) | b;
}

#define DETENT	 0
#define CW_1	 1
#define CW_2	 2
#define CW_3	 3
#define CCW_1	-1
#define CCW_2	-2
#define CCW_3	-3

void *Rotary::monitor(void *arg) {
	Rotary *rotary = static_cast<Rotary *>(arg);
	int state = DETENT;
	int last = -1;

	while (rotary->run_state) {
		int value = rotary->phase();

		if (value != last) {
			//printf("value: %x\n", value);

			switch (state) {
			case DETENT:
				if (value == 2) {
					state = CW_1;
				}
				else if (value == 1) {
					state = CCW_1;
				}
				break;
			case CW_1:
				if (value == 0) {
					state = DETENT;
				}
				else if (value == 3) {
					state = CW_2;
				}
				break;
			case CW_2:
				if (value == 2) {
				state = CW_1;
				}
				else if (value == 1) {
					state = CW_3;
				}
				break;
			case CW_3:
				if (value == 1) {
					state = CW_2;
				}
				else if (value == 0) {
					state = DETENT;
					rotary->_position++;
					//printf("CW! position: %d\n", rotary->_position);
				}
				break;
			case CCW_1:
				if (value == 0) {
					state = DETENT;
				}
				else if (value == 3) {
					state = CCW_2;
				}
				break;
			case CCW_2:
				if (value == 1) {
					state = CCW_1;
				}
				else if (value == 2) {
					state = CCW_3;
				}
				break;
			case CCW_3:
				if (value == 3) {
					state = CCW_2;
				}
				else if (value == 0) {
					state = DETENT;
					rotary->_position--;
					//printf("CCW! position: %d\n", rotary->_position);
				}
			}

			last = value;
		}
	}

	pthread_exit(NULL);
}

void Rotary::run() {
	run_state = true;
	if (pthread_create(&thread, NULL, monitor, (void *) this) != 0) {
		run_state = false;
	}
}

void Rotary::stop() {
	run_state = false;
}
