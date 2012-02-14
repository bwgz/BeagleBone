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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stepper.h>

#define PHASE 3000

#define SPEED_MIN	1
#define SPEED_MAX	100
#define SPEED_DELAY	10

Stepper::Stepper(int *numbers, int size) : current_phase(STATE_A), current_speed(100), current_position(0) {
	for (int i = 0; i < size; i++) {
		GPIO g(numbers[i]);
		gpio.push_back(g);
	}
}

void Stepper::set(int *values) {
	for (int i = 0; i < gpio.size(); i++) {
		gpio[i].value(*values++);
	}
}

void Stepper::A() {
	set((int[]) { 1, 0, 0, 0});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::AB() {
	set((int[]) { 1, 1, 0, 0});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::B() {
	set((int[]) { 0, 1, 0, 0});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::BC() {
	set((int[]) { 0, 1, 1, 0});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::C() {
	set((int[]) { 0, 0, 1, 0});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::CD() {
	set((int[]) { 0, 0, 1, 1});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::D() {
	set((int[]) { 0, 0, 0, 1});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::DA() {
	set((int[]) { 1, 0, 0, 1});
	usleep(PHASE);
	set((int[]) { 0, 0, 0, 0});
	usleep(PHASE);
}

void Stepper::step(int increment) {
	for (int i = 0; i < abs(increment); i++) {
		current_phase += (increment < 0) ? -1 : 1;

		if (current_phase > STATE_DA) {
			current_phase = STATE_A;
		}
		else if (current_phase < STATE_A) {
			current_phase = STATE_DA;
		}

		switch (current_phase) {
			case STATE_A:
				A();
				break;
			case STATE_AB:
				AB();
				break;
			case STATE_B:
				B();
				break;
			case STATE_BC:
				BC();
				break;
			case STATE_C:
				C();
				break;
			case STATE_CD:
				CD();
				break;
			case STATE_D:
				D();
				break;
			case STATE_DA:
				DA();
				break;
		}

		current_position += (increment < 0) ? -1 : 1;

		if (current_position > (POSITION_MAX - 1)) {
			current_position = 0;
		}
		else if (current_position < 0) {
			current_position = (POSITION_MAX - 1);
		}

		usleep((SPEED_MAX * SPEED_DELAY) - (current_speed * SPEED_DELAY));
	}
}
