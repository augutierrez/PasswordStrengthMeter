//Antonio Gutierrez
//CS 221
//PROJECT 1
// Professor Vahab
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

bool isStrongPassword(const char* username, const char* password);

bool isStrongDefaultPassword(const char* username, const char* password){
	bool length = false;
	bool uppercase= false;
	bool lowercase=false;
	bool number=false;
	bool string=false;
	bool differentThanUser= true;
	bool noSpecialChar=true;


	if (strlen(password) >= 8 && strlen(password) <= 15){ // checks to make sure the password is atleast 8 char long
		length = true;
	}

	int passLength = strlen(password);
	int userLength = strlen(username);
	int i = 0;
	for ( ; i < passLength - 1; i ++){ // checks if the first element in username is found within the password
		int b = 0;
		int sameAsUserCount = 0;
		if(username[b] == password[i]){ 
			sameAsUserCount++;
			int a = i + 1;
			b++;
			for(; a < passLength; a++){ // once first element in username is found in password, it iterates through the next few password elements to see if it matches the username
				if(username[b] == password[a]){
					sameAsUserCount++;
					b++;
				}
				else{
					a = passLength; //I only want to catch if the username's letters are used consecutively used.  If i wanted to check if the username is contained within password, then I would just delete this else statement.
				}
			}
		}
		if(sameAsUserCount == userLength){ // if these two numbers equal each other, it means the username is within the password
			differentThanUser = false;		// I could make this more sensitive as well by changing the if statement to if(sameUserCount > 3) that way the password does not contain even a small phrase from the username
			break;
		}
	}

	int stringCount = 0;
	i = 0; // starting point
	while(i < strlen(password))
	{
		if (isupper(password[i])){ // if an uppercase letter is identified, it sets the boolean to true
			uppercase = true;
			stringCount++;
			if(stringCount >= 4){ // to check if the 4 consecutive letters was met.
			string = true;
			}
		}
		else if (islower(password[i])){// if a lowercase letter is identified, it sets the boolean to ture
			lowercase = true;
			stringCount++;
			if(stringCount >= 4){ // to check if the 4 consecutive letters was met.
			string = true;
			}
		}
		else if (isdigit(password[i])){ // if a digit is identified, it sets the boolean to true
			number = true;
			stringCount = 0;
		}
		else{
			noSpecialChar = false; // if its anything but a letter or digit, its a special character which isn't allowed.
		}
		i++;
	}

	if (length && uppercase && lowercase && number && string && differentThanUser && noSpecialChar){ // checks to make sure all our 4 conditions were satisfied
		return true;
	}
	else { 
		return false;
	}

}
char* generateRandomPassword(char* default_password, const char* username)
{
	bool notStrong = true;

		
	printf("Generating a default password...\n");

	int num = rand()%3+3; // randomizes the number of elements that will be numbers
	int upper = rand()%3+3;// randomizes the number of elements that will be upper case letters
	int lower = rand()%3+3;// randomizes the number of elements lower will be lower case letters
	
	int lengthOfAll = num + upper + lower;
	char randomPassword[lengthOfAll + 1];
	
	while(notStrong){
		int i = 0;

		for (; i < num; i++){ 
			randomPassword[i] = rand()%(57-47) + 48; //adds characters to array numbers 
		}
		i = 0;

		for (; i < upper; i++){
			randomPassword[num + i] = rand()%(90-64) + 65; //adds characters to array upCase
		}
		i = 0;

		for (; i < lower; i++){
			randomPassword[num + upper + i] = rand()%(122-96) + 97; //adds characters to array lowCase
		}
		randomPassword[lengthOfAll] = '\0';
		
		strcpy(default_password, randomPassword);


		
		notStrong = !isStrongDefaultPassword(username, default_password);

	}
	printf("Generated default password: %s\n", default_password);
	return (default_password);
	
	
	
}

bool isStrongPassword(const char* username, const char* password) {
	bool length = false;
	bool uppercase= false;
	bool lowercase=false;
	bool number=false;
	bool string=false;
	bool differentThanUser= true;
	bool noSpecialChar=true;


	if (strlen(password) >= 8){ // checks to make sure the password is atleast 8 char long
		length = true;
	}
	
	
	int passLength = strlen(password);
	int userLength = strlen(username);
	int i = 0;
	for ( ; i < passLength - 1; i ++){ // checks if the first element in username is found within the password
		int b = 0;
		int sameAsUserCount = 0;
		if(username[b] == password[i]){ 
			sameAsUserCount++;
			int a = i + 1;
			b++;
			for(; a < passLength; a++){ // once first element in username is found in password, it iterates through the next few password elements to see if it matches the username
				if(username[b] == password[a]){
					sameAsUserCount++;
					b++;
				}
				else{
					a = passLength; //I only want to catch if the username's letters are used consecutively used.  If i wanted to check if the username is contained within password, then I would just delete this else statement.
				}
			}
		}
		if(sameAsUserCount == userLength){ // if these two numbers equal each other, it means the username is within the password
			differentThanUser = false; // I could make this more sensitive as well by changing the if statement to if(sameUserCount > 3) that way the password does not contain even a small phrase from the username
			break;
		}
	}

	int stringCount = 0;
	i = 0; // starting point
	while(i < strlen(password))
	{
		if (isupper(password[i])){ // if an uppercase letter is identified, it sets the boolean to true
			uppercase = true;
			stringCount++;
			if(stringCount >= 4){ // to check if the 4 consecutive letters was met.
			string = true;
			}
		}
		else if (islower(password[i])){// if a lowercase letter is identified, it sets the boolean to ture
			lowercase = true;
			stringCount++;
			if(stringCount >= 4){ // to check if the 4 consecutive letters was met.
			string = true;
			}
		}
		else if (isdigit(password[i])){ // if a digit is identified, it sets the boolean to true
			number = true;
			stringCount = 0;
		}
		else{
			noSpecialChar = false; // if its anything but a letter or digit, its a special character which isn't allowed.
		}
		i++;
	}

	if (length && uppercase && lowercase && number && string && differentThanUser && noSpecialChar){ // checks to make sure all our 4 conditions were satisfied
		printf("Strong password!\n");
		return true;
	}
	else { //if the conditions aren't met, user is prompted to try again.
		printf("Your password is week. Try again!\n");
		return false;
	}

}
	
int main(){
	srand(time(0));
	char username[30];
	char password[30];
	do{
		printf("Enter your username: ");// scans for user's desired username
		scanf("%s", username);
		printf("Enter a password: ");// scans for user's desired password
		scanf("%s", password);
	}
	while(!isStrongPassword(username, password));
	printf("\n");
	generateRandomPassword(password, username);
	return 0;
}

