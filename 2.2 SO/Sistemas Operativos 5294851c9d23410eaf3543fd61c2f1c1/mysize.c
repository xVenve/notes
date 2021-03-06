#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>


int main(int argc, char *argv[])
{

	DIR *descriptor;
	//Usamos el directorio actual
	char buffer[PATH_MAX];
	getcwd(buffer, PATH_MAX); //directorio guardado en buffer
	descriptor = opendir (buffer);

	if (descriptor == NULL){
		printf ("Error al abrir directorio \n");
		return -1;
	}
	//Leemos cada uno de los ficheros a del directorio al que apunta descriptor
	struct dirent *fichero_act;
	bucleLectura: while ( (fichero_act = readdir(descriptor) ) != NULL){
		//Usamos la función lseek
		if(fichero_act->d_type==DT_REG){
			//Abrimos el fichero en el que nos encontramos para encontrar su tamaño
			int descriptor_fichero = open(fichero_act->d_name, O_RDONLY);
			if (descriptor_fichero <0){
				printf("Error al abrir fichero: %s\n",fichero_act->d_name);
				goto bucleLectura;
			}
			int tamano_fichero = lseek(descriptor_fichero,0,SEEK_END);
			if (tamano_fichero <0){
				printf("Error al leer un fichero: %s\n",fichero_act->d_name);
				goto bucleLectura;
			}
			printf("%s\t%d\n",fichero_act->d_name,tamano_fichero);

			if (close(descriptor_fichero)<0){
				printf("Error al cerrar fichero: %s\n",fichero_act->d_name);
				return -1;
			}
		}

	}
	//Hemos terminado de leer, cerramos el directorio
	if (closedir(descriptor) == -1){
		printf("Error al cerrar directorio\n");
		return -1;
	}
	return 0;
}
