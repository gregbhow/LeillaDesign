/*
 * CryptageXOR.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Greg
 *
 *Algorithme de cryptage XOR
 *qui crypte les textes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// fonctions

//fonction de cryptage XOR
void encrypt (char phrase[1000],int decalage,int K){
	//declaration de variables
		int  j=0;//indice pour cesar
		char charactere ;//phrase apres chiffrement cesar
		char texte;//phrase apres chiffrement XOR
		int i=0;//indice pour XOR
		int length = strlen(phrase);//longueur de la phrase

		//chiffrement de cesar de la phrase a l'aide du decalage
		for ( j = 0 ; phrase[j] != '\0' ; ++j ){
			charactere = phrase[j] ;
			//decalage des characteres en minuscules
			if ( charactere >= 'a' && charactere <= 'z' ){
				charactere =  charactere+decalage;
				 if (charactere > 'z'){
					 charactere=charactere-26;
				 }
				 phrase[j]=charactere;
			}
			//decalage des characteres en majuscules
			else if ( charactere >= 'A' && charactere <= 'Z' ){
				charactere = charactere+decalage ;
				 if (charactere > 'Z'){
					 charactere=charactere-26;
				 }
				 phrase[j]=charactere;
			}
		}
		//chiffrement XOR du texte et de la cle de chiffrement
		for (i = 0 ; i < length ; i++){
				texte = phrase[i];
				texte = texte ^ K ;
				phrase[i]= texte ;
		}


}
//fin fonction de cryptage

//fonction de decryptage XOR
void decrypt(char phrase[1000],int decalage,int  K){
//declaration de variables
	int  j=0;//indice cesar
	char charactere ;//phrase apres dechiffrement de cesar
	int i=0;//indice XOR
	char texte;//phrase apres dechiffrement XOR
	int length = strlen(phrase); //longueur de la phrase

	//dechifrement XOR du texte et de la cle de chiffrement a l'aide du decalage
	for (i = 0 ; i < length ; i++){
			texte = phrase[i];
			texte = texte ^ K ;
			phrase[i]= texte ;
	}
	//dechiffrement de cesar de la phrase
	for ( j = 0 ; phrase[j] != '\0' ; ++j ){
		charactere = phrase[j] ;

//decalage pour les characteres minuscules
			if ( charactere >= 'a' && charactere <= 'z' ){
				charactere = charactere - decalage ;
				 if ( charactere < 'a'){
					 charactere =  charactere+26 ;
			     }
				phrase[j]= charactere ;
			}

//decalage pour les characteres majuscules
			else if ( charactere >= 'A' && charactere <= 'Z' ){
				charactere = charactere - decalage ;
					  if ( charactere < 'A'){
						  charactere = charactere+26 ;
					  }
				phrase[j]= charactere ;
			}
	}
}
//fin de la fonction de decryptage

//fonction convertion en binaire
void binaire (int ascii , char * bin){
char * rev = bin ;

	if ( NULL == bin)
		return ;
	while (ascii > 0){
			{
			if(ascii % 2 == 0){
			*bin = '0' ;
			}
			else{
				*bin = '1';
			}
			bin++;
			ascii =ascii /2 ;
				}
			*bin = '\0';
			_strrev(rev);
	}
}
//fin convertion en binaire


//fonction pour la cle de chiffrment K
int decalK(char mdp[50],int n,int decalage){
	//declarations des variables
	int i  ;// indice
	int hash ;// le hash(xor entre les characteres)
	char charactere; //charactere
	char BinaireDecalage[30];//binaire
	char BinaireK[30];//binaire
	char BinaireHash[30] ;//binaire en string
	int K;//cle de chiffrement k

	//hachage de chaque caractere du mot de passe
		for ( i = 0 ; i < n ; i++){
			charactere= mdp[i] ;
			hash ^= charactere;
	}
		//conversion du hash en binaire
		binaire(hash, BinaireHash);
		//  decalage en binaire
		binaire(decalage, BinaireDecalage);
		//calcul de la cle de chiffrement K
		 K = hash ^ decalage ;
		binaire(K, BinaireK);
       return K;
       //retourne la cle de chiffrement
}
//fin fonction de cle K

//fonction principale
int main (){
	//declaration des variables
	char phrase[1000] ;//phrase
	char mdp[50]; // mot de passe
	char file[50];//nom du fichier (pour le decryptage)
	int decalage=0;// decalage
	int choix=0;//choix du decryptage/cryptage/quitter
	int K=0;//cle de chiffrement K (pour la fonction (de)cryptage)
	int length=0;//longueur du mot de passe

	//declaration des differants fichiers textes
	FILE* texte;//fichier texte qui va sauvegarder la phrase ecrite
	FILE* decrypter;//fichier texte qui va sauvegarder la phase decryptee
	FILE* encrypter;//fichier texte qui va sauvegarder la phase cryptee
	FILE* fichier;//fichier texte qui va etre utiliser pour decrypter la phrase encrypter

	//ouvertures des differants fichiers textes en mode ecriture
	//(sauf fichier et encrypter pour le moment)



	//menu pour l'utilisateur
	printf("bonjour,je suis XORY un algorithme de cryptage XOR \n"
			"je vais devoir d'abord vous demander s'il faut crypter ou decrypter \n"
			"puis je vous vous demanderai:\n"
			"-la phrase puis le decalage et mot de passe dans le cas 'crypter'\n"
			"-le nom du fichier puis le decalage et le mot de passe dans le cas 'decrypter'\n");

	//choix pour encrypter/decrypter/quitter
	printf("\nsouhaitez vous:\n"
			"-crypter(1) \n"
			"-decrypter(2)\n"
			"-quitter(0) \n\n");

	printf("derniere info:\n"
			"TOUT CHOIX DIFFERANT DE CEUX PROPOSE SERA CONSIDERER COMME QUITTER (0) !!!\n\n");
	printf("saisissez le numero situee pres de l'action que vous voulez realiser... :)  \n");
	scanf("%d", &choix );

	switch(choix){
		//choix 1: quitter
		case 0:
			printf("Au plaisir de vous revoir 4dM!N...\n");
			system("pause");
			return 0;


		//choix 1: cryptage XOR
		case 1:
			//ouverture/creation du fichier text.txt
			texte = fopen("text.txt","w");
			printf("vous avez choisi 'crypter (1)' \n");
			//ouverture en mode ecriture/creation du fichier encrypter.txt
			encrypter = fopen("encrypt.txt","w");
			//demande de la phrase a saisir
			printf("ecrivez votre phrase a crypter: (1000 caracteres max et sur la meme ligne!)\n");
			getchar();
			gets(phrase);
			fprintf(texte,"%s",phrase);
			printf("vous trouverz une copie de votre texte dans text.txt \n");

			//demande du decalage
			printf("inserez votre decalage\n");
			scanf("%d",&decalage);
			//si le decalage saisi est superieur a 26
			if (decalage > 25){
				decalage=decalage%26;
			}

			//demande du mot de passe et calcule de la longueur de ce dernier
			printf("inserez votre mot de passe: (50 caracteres max !) \n");
			scanf("%s/n",mdp) ;
			length=strlen(mdp);

			//appel de la fonction Hash pour la cle de chiffrement
			K=decalK(mdp,length,decalage);

			//fonction de cryptage du texte
			encrypt(phrase,decalage,K);

			//ecriture et affichage du texte crypte dans le fichier texte
			fprintf(encrypter,"%s", phrase);
			printf("le texte cryptee donne:\n ");
			printf("%s\n",phrase);
			printf("\nvous retrouverez une copie dans encrypt.txt\n"
					"au plaisir de vous revoir 4dM!N \n");

			//fermeture des fichiers
			fclose(texte);
			fclose(encrypter);
			break;
		//fin cas cryptage

		//choix 2 :decryptage XOR
		case 2:
			//ouverture/creation du fichier decrypt.txt
			decrypter = fopen("decrypt.txt","w");
			printf("vous avez choisi 'decrypter (2)' \n");
			//demande du fichier a decrypter
			printf("entrez le nom du fichier (avec son extension!!!): \n");
			getchar();
			gets(file);

			//ouverture du fichier texte en mode lecture
			fichier = fopen(file,"r");

			if (fichier) {
			//si le fichier existe
			//lecture du fichier et ecriture dans la chaine de caracteres ces
				printf("ouverture du fichier...\n");
				printf("lecture reussie...\n");
				fscanf(fichier,"%[^\n]",phrase);

			}
			else{
			//si le fichier n'existe pas/non trouve
				 printf("Erreur 404 file not found...\n"
						 "redemarrez le programme pour reessayer...\n");
				 system("PAUSE");
				 return 0;
			}
			//fermeture du fichier
			fclose(fichier);

			//demande du decalage
			printf("\ninserez le decalage\n");
			scanf("%d",&decalage);
			//si le decalage saisi est superieur a 26
			if (decalage > 25){
					decalage=decalage%26;
				}
			//demande du mot de passe et calcule de la longueur de ce dernier
			printf("inserez le mot de passe: (50 caracteres max !) \n");
			scanf("%s/n",mdp) ;
			length=strlen(mdp);

			//appel de la fonction Hash pour la cle de chiffrement
			K=decalK(mdp,length,decalage);

			//fonction de decryptage du fichier texte
			decrypt(phrase,decalage,K);

			//ecriture et affichage du texte decrypte dans le fichier texte
			fprintf(decrypter,"%s",phrase);
			printf("\nle texte decryptee donne: %s\n",phrase);
			printf("\nvous retrouverez une copie dans decrypt.txt\n"
					"au plaisir de vous revoir 4dM!N \n");

			//fermeture du fichier decrypt.txt
			fclose(decrypter);
			break;
			//fin cas decryptage

		//si le choix saisi ne correpond a aucune proposition donnee
		default:
			printf("Au plaisir de vous revoir 4dM!N...\n");
			system("pause");
			return 0;
			//arret dy programme
}
	system("pause");
	return 0 ;
}
//fin de la fonction principale

