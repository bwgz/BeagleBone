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

#ifndef _STEPPER_H
#define _STEPPER_H

#include <string>
#include <vector>
#include <gpio.h>

using namespace std;

#define STATE_A		0
#define STATE_AB	1
#define STATE_B		2
#define STATE_BC	3
#define STATE_C		4
#define STATE_CD	5
#define STATE_D		6
#define STATE_DA	7

#define DELAY_INC	1000
#define POSITION_MAX	(64 * 64)

class Stepper {
private:
	int current_phase;
	int current_speed;
	int current_position;

	vector<GPIO> gpio;

	void set(int *values);

	void A();
	void AB();
	void B();
	void BC();
	void C();
	void CD();
	void D();
	void DA();

public:
	Stepper(int *numbers, int size);

	void step(int increment);

	int phase() {
		return current_phase;
	}

	int speed() {
		return current_speed;
	}

	void speed(int value) {
		if (value > 100) {
			current_speed = 100;
		}
		else if (value < 1) {
			current_speed = 1;
		}
		else {
			current_speed = value;
		}
	}

	int position() {
		return current_position;
	}
};

#endif
