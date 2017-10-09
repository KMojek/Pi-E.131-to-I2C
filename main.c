#include <stdio.h>
#include <string.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <fcntl.h>
#include <unistd.h>

#include <linux/i2c-dev.h>

#define BUFSIZE 2048

int fd1, fd2;

int initLights()
{
   char buff[32];

   fd1 = open( "/dev/i2c-1", O_WRONLY );
   fd2 = open( "/dev/i2c-1", O_WRONLY );

   if ( fd1 < 0 )
   {
      printf( "Uh-oh... failed to open I2C bus on chip 1!!\n" );
      return -1;
   }
   if ( fd2 < 0 )
   {
      printf( "Uh-oh... failed to open I2C bus on chip 2!!\n" );
      close( fd1 );
      return -1;
   }

   /* open file handles */
   if ( ioctl( fd1, I2C_SLAVE, 0x20 ) < 0 )
   {
      printf("Uh-oh... failed to configure I2C bus on chip 1 for writing!!\n");
      close( fd1 );
      fd1 = -1;
      return -1;
   }

   if ( ioctl( fd2, I2C_SLAVE, 0x21 ) < 0 )
   {
      printf("Uh-oh... failed to configure I2C bus on chip 2 for writing!!\n");
      close( fd2 );
      fd2 = -1;
      return -1;
   }

   /* Configure for writing */
   buff[0] = 0x00; buff[1] = 0x00;
   write( fd1, buff, 2 );
   write( fd2, buff, 2 );

   buff[0] = 0x01; buff[1] = 0x00;
   write( fd1, buff, 2 );
   write( fd2, buff, 2 );

   return 0;
}


int main()
{
   struct sockaddr_in sin;
   char buff[32];
   int sd, bindStatus;

   initLights();

   sd = socket( AF_INET, SOCK_DGRAM, 0 );

   memset( &sin, sizeof(struct sockaddr_in), 0 );
   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = INADDR_ANY;
   sin.sin_port = htons( /*6454*/5568 );

   bindStatus = bind( sd, (struct sockaddr *)&sin, sizeof(struct sockaddr_in) );
   printf("bind() status - %d\n", bindStatus );

   int64_t prevStatus[4] = { 0, 0, 0, 0 };
   for ( ;; )
   {
      unsigned char buf[BUFSIZE];
      int recvLen;
      struct sockaddr_in remote;
      socklen_t addr_len = sizeof(struct sockaddr_in);

      recvLen = recvfrom( sd, buf, BUFSIZE, 0, (struct sockaddr *)&remote, &addr_len );

      if ( recvLen > 32 ) // 32 channels
      {
         char intensities[32];
         int64_t status[4];

         memcpy( intensities, buf+recvLen-32, 32 );
         memcpy( status, buf+recvLen-32, 32 );

         if ( status[0] != prevStatus[0] )
         {
            //printf("1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
            //   intensities[0], intensities[1], intensities[2], intensities[3],
            //   intensities[4], intensities[5], intensities[6], intensities[7] );
            buff[1] = 0x00;
            if ( intensities[ 0] ) buff[1] |= 0x01;
            if ( intensities[ 1] ) buff[1] |= 0x02;
            if ( intensities[ 2] ) buff[1] |= 0x04;
            if ( intensities[ 3] ) buff[1] |= 0x08;
            if ( intensities[ 4] ) buff[1] |= 0x10;
            if ( intensities[ 5] ) buff[1] |= 0x20;
            if ( intensities[ 6] ) buff[1] |= 0x40;
            if ( intensities[ 7] ) buff[1] |= 0x80;

            buff[0] = 0x14;
            write( fd1, buff, 2 );

            prevStatus[0] = status[0];
         }

         if ( status[1] != prevStatus[1] )
         {
            //printf("2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
            //   intensities[8], intensities[9], intensities[10], intensities[11],
            //   intensities[12], intensities[13], intensities[14], intensities[15] );
            buff[1] = 0x00;
            if ( intensities[ 8] ) buff[1] |= 0x01;
            if ( intensities[ 9] ) buff[1] |= 0x02;
            if ( intensities[10] ) buff[1] |= 0x04;
            if ( intensities[11] ) buff[1] |= 0x08;
            if ( intensities[12] ) buff[1] |= 0x10;
            if ( intensities[13] ) buff[1] |= 0x20;
            if ( intensities[14] ) buff[1] |= 0x40;
            if ( intensities[15] ) buff[1] |= 0x80;

            buff[0] = 0x15;
            write( fd1, buff, 2 );

            prevStatus[1] = status[1];
         }

         if ( status[2] != prevStatus[2] )
         {
            //printf("3: %02x %02x %02x %02x %02x %02x %02x %02x\n",
            //   intensities[16], intensities[17], intensities[18], intensities[19],
            //   intensities[20], intensities[21], intensities[22], intensities[23] );
            buff[1] = 0x00;
            if ( intensities[16] ) buff[1] |= 0x01;
            if ( intensities[17] ) buff[1] |= 0x02;
            if ( intensities[18] ) buff[1] |= 0x04;
            if ( intensities[19] ) buff[1] |= 0x08;
            if ( intensities[20] ) buff[1] |= 0x10;
            if ( intensities[21] ) buff[1] |= 0x20;
            if ( intensities[22] ) buff[1] |= 0x40;
            if ( intensities[23] ) buff[1] |= 0x80;

            buff[0] = 0x14;
            write( fd2, buff, 2 );

            prevStatus[2] = status[2];
         }

         if ( status[3] != prevStatus[3] )
         {
            //printf("4: %02x %02x %02x %02x %02x %02x %02x %02x\n",
            //   intensities[24], intensities[25], intensities[26], intensities[27],
            //   intensities[28], intensities[29], intensities[30], intensities[31] );
            buff[1] = 0x00;
            if ( intensities[24] ) buff[1] |= 0x01;
            if ( intensities[25] ) buff[1] |= 0x02;
            if ( intensities[26] ) buff[1] |= 0x04;
            if ( intensities[27] ) buff[1] |= 0x08;
            if ( intensities[28] ) buff[1] |= 0x10;
            if ( intensities[29] ) buff[1] |= 0x20;
            if ( intensities[30] ) buff[1] |= 0x40;
            if ( intensities[31] ) buff[1] |= 0x80;

            buff[0] = 0x15;
            write( fd2, buff, 2 );

            prevStatus[3] = status[3];
         }
      }
   }

   buff[0] = 0x14; buff[1] = 0x00;
   write( fd1, buff, 2 );
   write( fd2, buff, 2 );
   buff[0] = 0x15; buff[1] = 0x00;
   write( fd1, buff, 2 );
   write( fd2, buff, 2 );

   close( fd2 );
   close( fd1 );

   close( sd );
}
