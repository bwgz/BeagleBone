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

#ifndef _ROTARY_H
#define _ROTARY_H

#include <pthread.h>
#include <gpio.h>

class Rotary {
private:
	int _position;

	GPIO *A;
	GPIO *B;

	Rotary();

	bool run_state;
	pthread_t thread;
	static void *monitor(void *arg);

public:

	Rotary(int a, int b);
	~Rotary();

	unsigned phase();
	int position() {
		return _position;
	}

	void run();
	void stop();
};

#endif
