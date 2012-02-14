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

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <ain.h>

AIN::AIN(int number) {
	this->number = number;

	char buffer[1024];
	sprintf(buffer, "/sys/devices/platform/tsc/ain%d", number);
	path = buffer;
}

AIN::~AIN() {
}

int AIN::value() {
	int value;
	ifstream in;
	in.open(path.c_str());
	in >> value;
	in.close();

	return value;
}

void AIN::dump() {
	cout << "number: " << number << endl;
	cout << "path: " << path << endl;
}
