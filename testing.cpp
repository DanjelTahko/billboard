#include <iostream>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

using namespace std;
struct termios tty;

int main() {

    int serial_port = open("/dev/cu.usbmodem11401", O_RDWR);

    while(1) {
        unsigned char *word;
        cin >> word;
        cout << word << endl;
        write(serial_port, word, sizeof(word));
        cout << "Size of = " << sizeof(word) << endl;
        if (*word == 'q') {
            return 0;
        }
    }
    close(serial_port);
}
