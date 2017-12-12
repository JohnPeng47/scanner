#include <ctype.h> //implements some bnasic checks
#include <limits.h>

int genmask(char* cidr);
int strtoip(char *ipadr);
long iptonum(char* cidr, char delimeter);

void main(int argc, char** argv){ //argc is the number of arguments, argv is pointer to char pointers (ie. strings)
    char *ipadr;

    if(argc < 2){
        printf("Please specify ip range");
        exit(0);
    }
    strtoip(argv[1]);
    
}

int strtoip(char *ipadr){
    char *ch; int i=0; long check_mask; int check_bit; int sigbits;
    char buff[36], cidr[3]; 

    ch = buff; //point ch at the beginning of the character buffer
    cidr[sizeof(cidr)-1] = '\0'; //null terminate string

    for(;*ipadr != '\0'; ipadr++){
        if(*ipadr == '/'){
            printf("range detected\n");
            cidr[0] = *(ipadr+1);
            cidr[1] = *(ipadr+2);
            sigbits = atoi(cidr);
            
            long iprange = genmask(cidr) & sigbits;

            check_mask = 1 << sigbits; //we are going to use this to check if the most significant bit has been 
                                       //changed
            printf("iptonum: %ld\n", iptonum(cidr, "."));
            printf("check: %ld\n", check_mask);
        }
        *ch = *ipadr;
        ch++;
    }
    printf("ip addr: %s\n", buff);
    printf("CIDR: %ld\n", genmask(cidr)); //need to use %ld or else defaults to printing 16bit 
    // printf("max int: %x",  );
}  

long iptonum(char* cidr, char delimeter){
    long ipadr = 0; char* ch; char* segment;
    ch = cidr;

    int i;
    for(i=3; i >= 0; i--){ //iterates through each of the subsections of the ip address
        segment = calloc(4,sizeof(char));
        char* freeme = segment;
        for(; *ch != delimeter; ch++){
            *segment = *ch;
            segment++;
        }   
        ch++; //when loop exits ch points to delimeter so incrementsc
        printf("Segment%d: %s\n",i,segment);
        ipadr += atoi(segment) << 8 * i;
        segment = freeme;
        free(segment);
    }
    return ipadr;
}
//returns a mask that masks the first n bits (n being number pointed to by cidr)
int genmask(char* cidr){
    char buff[32];
    int i = 0; long j = 0;
    int mask_len = atoi(cidr); 
    for(i = 0; i < mask_len; i++){
        j = (j << 1) + 1; 
    }
    return j << (32 - mask_len); 
}
 