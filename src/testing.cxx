#include "avrcpp/testing.hpp"
#include <avr/io.h>
#include <stdio.h>

namespace
{
int std_output(char character, FILE *stream)
{
        while ((UCSR0A & (1 << UDRE0)) == 0) {};
        UDR0 = character;
        return 0;
}

FILE uart_fd = {
    .flags = _FDEV_SETUP_WRITE,
    .put = std_output
};
}

namespace avrcpp
{

tests_base::tests_base()
{
    constexpr auto BAUD_RATE = 38400u;
    constexpr unsigned int ubrr = F_CPU / 16u / BAUD_RATE - 1u;
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);

    stdout = &uart_fd;
}

} // namespace avrcpp
