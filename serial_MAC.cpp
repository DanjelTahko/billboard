#include <iostream>

using namespace std;

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

int serial_port = open("/dev/tty.usbmodem11401", O_RDWR); // '0_RDWR' - read/write

struct termios tty;

int main () {

    // Check for errors
    if (serial_port < 0) {
        cout << "Error " << errno << "from open: " << strerror(errno) << endl;  
    }

    if (tcgetattr(serial_port, &tty) != 0) {
        cout << "Error " << errno << " from tcgetattr " << strerror(errno) << endl;
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication 
    tty.c_cflag &= ~CSIZE; // Clear all the size bits
    tty.c_cflag |= CS8; // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON; // Canonical mode is disabled
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    // Sets both the input and output speeds at the same time
    cfsetspeed(&tty, B9600);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        cout << "Error " << errno << " from tcsetattr: " << strerror(errno) << endl;
    }

    unsigned char msg[] = {'H', 'e', 'l', 'l', 'o'};
    write(serial_port, msg, sizeof(msg));

    // Allocate memory for read buffer, set size according to your needs
    char read_buf [256];
    int n = read(serial_port, &read_buf, sizeof(read_buf));

    close(serial_port);

    return 0;

}



