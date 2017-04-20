/*
 ============================================================================
 Name        : file_server.c
 Author      : Lars Mortensen
 Version     : 1.0
 Description : file_server in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <iknlib.h>

#define SIZE 1000

void sendFile(char *fileName, long fileSize, int outToClient);

/*
 * Opretter en socket.
 * Venter på en connect fra en klient.
 * Modtager filnavn
 * Finder filstørrelsen
 * Kalder metoden sendFile
 * Lukker socketen og programmet
 *
 * @param argc Antal argumenter
 * @param argv Argumenterne i et array
 */
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[SIZE];
    struct sockaddr_in serv_addr, cli_addr;   // Oprettet structs til at indeholde server og client adresseinformation
    int n;
    long fileSize = 0;

    if( argc < 2 )   // Hvis man ikke har givet en port, kan man ikke skabe forbindelse. Fejlmeddelse. Terminering af programmet.
    {
        fprintf(stderr, "Error, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);   // Opretter socket på serveren, 
	//bruger internet, Sock stream data transfer(TCP) og vælger selv TCP for optimering(0).
    if (sockfd < 0)
        error("ERROR opening socket");




    bzero((char *) &serv_addr, sizeof(serv_addr)); // Sætter 0'er i vores serverbuffer
    portno = atoi(argv[1]); // Laver portnummeret fra string til integer

    serv_addr.sin_family = AF_INET; // Server familien er internet
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Henter IP adresse for server
    serv_addr.sin_port = htons(portno); // Indstiller serverens port nummer


    printf( "Socket forbundet\n" );

    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) // Frobinder socket til adresse på server
        error("ERROR on binding\n");


    while(1)    // Holder serveren åben.
    {

		listen(sockfd, 5); // Lytter efter forbindelse på socket. Maksimal antal tilslutninger 5.

		printf( "Listening for socket connection\n" );
		clilen = sizeof(cli_addr); // Længden af client filen

		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); // Acceptere forbindelse til client

    if(newsockfd < 0)
        error("ERROR on accept\n");

    printf( "socket connection accepted\n" );
    bzero(buffer,SIZE); // Fylder buffer med 0


    readTextTCP( buffer, SIZE, newsockfd); //Læser hvad clienten har sent til serveren
    printf("Filename is: %s\n", buffer);

    writeTextTCP(newsockfd, buffer);
    //fileSize = check_File_Exists( buffer ); // Kontrollere om filen eksistere og gemmer størrelsen i filesize

    //sendFile( buffer, fileSize, newsockfd ); //Sender filen til clienten
    close(newsockfd); 							//Lukker forbindelsen til clienten
    }


    exit(1);
}

/*
 * Sender filstørrelsen
 * Hvis filstørrelsen = 0 sendes indhold af filen ikke
 * ellers
 * åbnes filen for at læse den og sende indhold i blokke af 1000 bytes til klienten.
 * Luk filen.
 *
 * @param fileName Det fulde filnavn incl. evt. stinavn.
 * @param fileSize Størrelsen på filen.
 * @param outToClient Stream for at skrive til serveren.
 */
void sendFile(char *fileName, long fileSize, int outToClient)
{
    if(fileSize == 0) //Tjekker fil-størrelse
		printf("File does not exist\n");
    else
	{
        printf( "Going to send file now\n" );

		char buffer[SIZE] = ""; 				//Opretter buffer-array med størrelse SIZE (1000)
		char fileBlock[SIZE] = {"0"};			//Opretter fileblock-array med størrelse SIZE (1000)
		int n = 0, percentage = 0, cond = 0;	//Oprettelse af variable
		long fileLeft = fileSize;

		sprintf(buffer, "%ld", fileSize );		//Laver størrelsen af fileSize om til en long-string, gemt i buffer
		writeTextTCP(outToClient, buffer);		//Send fileSize to client


		printf( "Sending fileSize = %ld\n", fileSize );

        int fd = open( fileName , O_RDONLY); //Åbner filen der skal sendes

		printf( "Opening file for reading\n" );

		while( fileLeft > 0 )
		{
			n = read(fd,fileBlock,SIZE); 											//Læser "SIZE"-bytes fra "fd" og smider dem over i "fileBlock"

			write(outToClient, fileBlock, n);										//Sender n-bytes i "fileBlock" til clienten

			fileLeft -= n;															// Tæller antal læste bytes op og trækker fra antal bytes tilbage i filen																// Tæler antal læste bytes op
			bzero( fileBlock, SIZE); 												//Resetter fileBlock

			printf( "Sending %d to TCP. Total bytes left: %ld\n", n, fileLeft );


		}
		printf( "\nFile sent.\n Sent %f MB\n", (float)((float)fileSize/1000)/1000 ); //fra bytes til MB

		printf( "closing file.\n" );
		close(fd); //Lukker filen
	}
}
