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

#include <stdio.h>
#include <stdlib.h>
#include <beaglebone.h>
#include <rotary.h>

int main(int argc, char **argv) {
	int number_a = GPIO2_6;
	int number_b = GPIO2_7;

	if (argc == 3) {
		number_a = atoi(argv[1]);
		number_b = atoi(argv[2]);
	}

	Rotary rotary(number_a, number_b);

	rotary.run();
	while (1) {
		printf("phase: %d  position: %d\n", rotary.phase(), rotary.position());
	}
	rotary.stop();

}
