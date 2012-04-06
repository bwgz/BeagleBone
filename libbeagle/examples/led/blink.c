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

#include <dirent.h>
#include <stdio.h>

/*
 * If the sysfs GPIO does not exist then create it.
 */
void setup(int number) {
	DIR *dir;
	char path[4096];

	sprintf(path, "/sys/class/gpio/gpio%d", number);
	if (opendir(path) == NULL) {
		FILE *fp = fopen("/sys/class/gpio/export", "w");
		if (fp != NULL) {
			fprintf(fp, "%d", number);
			fclose(fp);
		}
	}
}

/*
 * Remove the sysfs GPIO.
 */
void teardown(int number) {
	FILE *fp = fopen("/sys/class/gpio/unexport", "w");
	if (fp != NULL) {
		fprintf(fp, "%d", number);
		fclose(fp);
	}
}

void blink(int number, int blinks) {
	char path[4096];

	sprintf(path, "/sys/class/gpio/gpio%d/direction", number);
	FILE *fp = fopen(path, "w");
	if (fp != NULL) {
		int i;

		for (i = 0; i < blinks; i++) {
			rewind(fp);
			fprintf(fp, "high");
			fflush(fp);
			sleep(1);

			rewind(fp);
			fprintf(fp, "low");
			fflush(fp);
			sleep(1);
		}

		fclose(fp);
	}
}

int main(int argc, char **argv) {
	int number = 72;
	int blinks = 10;
	char gpio[4096];

	if (argc == 2) {
		number = atoi(argv[1]);
	}

	setup(number);
	blink(number, blinks);
	teardown(number);
}
