#include <string.h>

class info
{
    private:
        int health;
        int power;
        char payload[10];

    public:
        info()
        {
            health = 99;
            power = 87;
            strcpy(payload, "testtest!");
        }

        int get_health()
        {
            return this -> health;
        }

        int get_power()
        {
            return this -> power;
        }

        char* get_payload()
        {
            return this -> payload;
        }
};