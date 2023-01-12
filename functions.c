/******************************************************************************
 * @file: functions.c
 *
 * htnguyen23
 * Huong Nguyen
 * 908 071 6005
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Huong Nguyen (htnguyen23@wisc.edu)
 * @modified: 10/7/2021
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...

int isLetter(char toCheck) {

	// determine wether or not the char is a letter using ASCII comparison
	if ((toCheck >= 'A' && toCheck <= 'Z') || (toCheck >= 'a' && toCheck <= 'z'))
		return 1; // True (is a letter)
	else
		return 0; // False 

}

int isDigit(char toCheck) {

	// determine wether or not the char is a digit using ASCII comparison
	if (toCheck >= '0' && toCheck <= '9') 
		return 1; 
	else
		return 0;  

}

/*
int isValid(char array[], char special[]) {

	// determine wether or not the string (char array) contains only valid character (letters & digits)
	// other characters considered valid are specified in special array paramater, w/ the first element being 1 (yes special char) or 0 (no special char to include)

}
*/

int hasChar(char array[], char lookFor) {
	int i = 0;
	char currChar = array[i];
	while (currChar != '\0') {
		if (currChar == lookFor) {
			return 1;
		}
	i++;
	currChar = array[i];
	}
	return 0;
} 

int stringLen(char array[]) {

	// use sizeof to find the number of elements in an array (but this doens't work for function parameter array):
	// return (sizeof(array) / sizeof(array[0]));
	// using a while loop to count the number of elements -> is there a better way?
	int i = 0;
	int nextElem = 1; 
	char elem;
	int len = 0;
	while (nextElem) {
		elem = array[i];
		if (elem != '\0') { 
			len += 1;
			i ++;
		}
		else {
			nextElem = 0;
		}
	}
	return len;

}

int compare(char strA[], char strB[]) {

	// compare wether or not two strings are equal by iterating through both string arrays and comparing each char
	if (stringLen(strA) != stringLen(strB))
		return 0;
	//int matchFlag = 1;
	for (int i = 0; i < stringLen(strA); i++) {
		if(!(strA[i] == strB[i])) 
			//matchFlag = 0;
			return 0;
	}
	return 1;

}

char* substring(char str[], int starti, int endi) {
	// get a substring from str[] with starting index starti (inclusive), and ending index endi (exclusive) 
	char substr[512];
	int curri = 0;
	for (int i = starti; i < endi; i++) {
		substr[curri] = str[i];
		curri++;
	}
	return substr;
}


/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n");

	int strLen = stringLen(user);
	if(!isLetter(user[0])) { 
    		printf(ERROR_01_USER_START_INVALID);
		return 0;
	}
	else if (strLen > MAX_USERNAME_LEN) {
    		printf(ERROR_02_USER_LEN_INVALID);
		return 0;
	}
    	// passed 2/3 requirements - testing for valid chars here
	for (int i = 0; i < strLen; ++i) 
	{
		char currChar = user[i];
		if (!(isLetter(currChar) || isDigit(currChar) || (currChar == '_')))  // is == comparing address or content? 
		{
			printf(ERROR_03_USER_CHARS_INVALID);
			return 0;
    		}
	}
	/* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) { 

    /* BEGIN MODIFYING CODE HERE */
	// split email into its 4 parts
	char *at_pointer = 0; // initialized to undefined -> on the CSL machine, pointers can't start at 0?
	char *end_pointer;
	int strLen = stringLen(email);
	end_pointer = &email[strLen];
	int nameLen = 0;
	// get at_pointer
	for (int i = 0; i < strLen; i++) {
		if (email[i] == '@') {
			at_pointer = &email[i];
			nameLen = i;
			if (i == 0) {
				printf(ERROR_04_EMAIL_MISSING_NAME);  // example @domain.com
				return 0;
			}
			break;
		}
	}
	// check email starting character
	if (!isLetter(email[0])) {
    		printf(ERROR_05_EMAIL_START_INVALID);
		return 0;
	}
	// check email length
    	if (nameLen > MAX_EMAIL_LEN) {
		printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
		return 0;
   	}
	// check valid email characters
	char *cp_pointer;	// Q: initialzation -> *ptr, gets address -> ptr, dereferencing -> *ptr?
	cp_pointer = at_pointer;  // copy at_pointer so we can interate backwards through email
	char currChar;
	//if (*cp_pointer == '@') 
	//	printf("\nYes @ character\n");
	//printf("Checking each char for if it's a letter or digit\n");
	for (int i = 0; i < nameLen; i++) {
	//	printf("\ni: %d   ", i);
		*cp_pointer--;
		currChar = *cp_pointer;
	//	printf("pointer being tested: %c\n", currChar);
		if (!(isLetter(currChar) || isDigit(currChar))) {
			printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
			return 0;
		}
	}
    	// check @ exists
	if (at_pointer == 0) {
		printf(ERROR_08_EMAIL_MISSING_SYMBOL); // example mike.wisc.edu
    		return 0;
	}
	// check missing domain
	cp_pointer = end_pointer;
	for (int i = 0; i < 5; i++) {
		*cp_pointer--;
	}
	if (*cp_pointer == '@') { // can I use "cp_pointer == at_pointer"?
		printf(ERROR_09_EMAIL_MISSING_DOMAIN);  // example mike@.edu
		return 0;
	}
	// check domain length
	int domainLen = 0;
	while (*cp_pointer != '@') {
		domainLen++;
		*cp_pointer--;
	}
	if (domainLen > MAX_DOMAIN_LEN) {
		printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
		return 0;
	}
	// check valid domain start
	cp_pointer = at_pointer;
	*cp_pointer++;
	int subDomFlag = 1;
	for (int i = 0; i < domainLen; i++) {
		currChar = *cp_pointer;
		//printf("\ncurrChar: %c\n", currChar);
		if (currChar == '.') {
			subDomFlag = 1;
			*cp_pointer++;
			continue;
		}
		if (subDomFlag) {
			//printf("\nchecking valid domain start character\n");
			if (!isLetter(currChar)) {
    				printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
				return 0;
			}
			subDomFlag = 0;
		}
		// check valid domain characters
		else {
			//printf("\nchecking valid domain characters\n");
			if (!(isLetter(currChar) || isDigit(currChar))) {
	    			printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
				return 0;
			}
		}
		*cp_pointer++;
    	}
	// check valid top domain
	char top1[] = ".edu";
	char top2[] = ".com";
	char top3[] = ".net";
	//char top3[] = ['.','n','e','t','\0'];
	int matchFlag = 0;
	char userTopDom[5];
	cp_pointer = end_pointer;
	for (int i = 4; i >= 0; i--){
		userTopDom[i] = *cp_pointer;
		*cp_pointer--;
	}
	if (compare(userTopDom, top1))
		matchFlag = 1;
	if (compare(userTopDom, top2))
		matchFlag = 1;
	if (compare(userTopDom, top3))
		matchFlag = 1;
	if (!matchFlag) {
		printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
		return 0;
	}
    /* END MODIFYING CODE HERE */
    	printf(SUCCESS_2_EMAIL);
    	return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
	int strLen = stringLen(pwd);
	// check password for spaces
	if (hasChar(pwd, ' ')) {
    		printf(ERROR_14_PWD_SPACES_INVALID);
		return 0;
	}
	// check password for 8 character minimum
	if (strLen < MIN_PASSWORD_LEN) {
    		printf(ERROR_15_PWD_MIN_LEN_INVALID);
		return 0;
	}
	// check password length maximum
	if (strLen > MAX_PASSWORD_LEN) {
    		printf(ERROR_16_PWD_MAX_LEN_INVALID);
		return 0;
	}
	// check password for uppercase and lowercase character
	int upperFound = 0;
	int lowerFound = 0;
	char currChar;
	for (int i = 0; i < strLen; i++) {
    		currChar = pwd[i];
		if (currChar >= 'A' && currChar <= 'Z') {
			upperFound = 1;
		}
		if (currChar >= 'a' && currChar <= 'z') {
			lowerFound = 1;
		}
	}
	if (!upperFound) {
		printf(ERROR_17_PWD_MIN_UPPER_INVALID);
		return 0;
	}
	if (!lowerFound) {
		printf(ERROR_18_PWD_MIN_LOWER_INVALID);
		return 0;
	}
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
	int pwd1Len = stringLen(pwd1);
	int pwd2Len = stringLen(pwd2);
	// iterate through both strings to see if every char matches
	if (pwd1Len != pwd2Len) {
    		printf(ERROR_19_PWD_MATCH_INVALID);
		return 0;
	}
	for (int i = 0; i < pwd1Len; i++) {
		if (pwd1[i] != pwd2[i]) {
			printf(ERROR_19_PWD_MATCH_INVALID);
			return 0;
		}
	}
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    	printf("%s", message);
    	fgets(data, MAX_LENGTH, stdin);
   	/* BEGIN MODIFYING CODE HERE */
	// while loop through array to find \n character to replace with \0
	int i = 0;
	int nextElem = 1;
	char elem;
	while (nextElem) {
		elem = data[i];
		if (elem != '\n') 
			i++;
		else {
			data[i] = '\0';
			nextElem = 0;
		}
	}
    	/* END MODIFYING CODE HERE */
    	return;
}

