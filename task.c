#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int hexConvert (char hex[]) {

    int decimal = 0, base = 1;
    int value, length;
    char a = 'a';
    length = 4; // the length of the hex array will always be two bytes according to definition
    for(int i = length--; i >= 0; i--)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base *= 16;
        }
        else if(hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base *= 16;
        }
        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base *= 16;
        }
    }
    return decimal;

}



int main(int argc, char* argv []) {
    FILE *myFile;
    FILE *completePackets;
    char buf[8];
    char pid[2];//array to store the header of the packets
    char numPackets[2];
    char byteNumber[1];
    size_t decByteNum;
    //initializes a file object that contains the binary file.
    //myFile = fopen("Given_Files/packetized_script", "r");
    myFile = fopen(argv[1], "rb");
    completePackets = fopen("Complete_Packets", "wb");
    //checks if the inputted file is valid
    //   if(!myFile) {
    //  printf("Cannot open file");
    //  return 1;
    // }
    //reads the first two bytes(packet id) and puts them in an array
    fread(pid, 2, 1, myFile);
    fwrite(pid, 2, 1, completePackets);
    //reads the third and fourth bytes(number of packets) and puts them in an array
    fread(numPackets, 2, 1, myFile);
    fwrite(numPackets, 2, 1, completePackets);
    //reads the fifth and sisxth bytes(numbers of bytes in the packet) and puts them in an array
    fread(byteNumber, 2, 1, myFile);
    fwrite(byteNumber, 2, 1, completePackets);
    for(int i = 0; i < 2; i++) {
        printf("%d", byteNumber[0]);
    }
    //prints the first packet header separated into the pid, #ofpackets, and #ofbytesinthepacket.
    printf("packet header: \n");
      for(int i = 0; i < 2; i++) {
      printf("%02x ", (unsigned char)pid[i]);
     }
    for(int i = 0; i < 2; i++) {
        printf("%02x ", (unsigned char)numPackets[i]);
    }
    for(int i = 0; i < 2; i++) {
        printf("%02x ", (unsigned char)byteNumber[i]);
    }
    printf("\n");
    //reads and prints the data in the packet
    //the length came from the 5th and 6th bytes in the file
    for(int i = 0; i < 127; i ++)  {
        fread(buf,1,8,myFile);
        fwrite(buf, 1, 8, completePackets);
        for(int i = 0; i < 8; i++) {
            printf("%02x ", (unsigned char)buf[i]);
        }
        printf("\n");
    }

    printf("\n\n\n");


}
