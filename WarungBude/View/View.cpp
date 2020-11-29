#include<stdio.h>
#include<time.h>
#include"../Controller/Controller.h"

int mainMenu(){
    printf("System: %s\n", detectOS());
    outputTime();
    printf("\n");
    printf("1. Add Dish\n");
    printf("2. Remove Dish\n");
    printf("3. Add Customer\n");
    printf("4. Search Customer\n");
    printf("5. View Warteg\n");
    printf("6. Order\n");
    printf("7. Payment\n");
    printf("8. Exit Warteg\n");
    int input = validateNumberInput();
    return input;
}

int addDishMenu(){
    addDish();
    printf("The dish has been added\n");
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}

int removeDishMenu(){
    if(dishHead == NULL){
        printf("There\'s no dish !\n");
        printf("Press enter to continue...\n");
        getchar();
        return 0;
    }
    outputMenu();
    printf("Insert dish\'s name to be deleted: ");
    char nameInput[255];
    scanf("%[^\n]", nameInput);
    getchar();
    bool valid = removeDish(nameInput);
    if(valid){
        printf("The dish has been removed\n");
    } else {
        printf("The dish doesn\'t exist\n");
    }
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}

int addCustomerMenu(){
    validateCustomer();
    printf("Customer has been added\n\n");
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}

int searchCustomerMenu(){
    char nameInput[255];
    Person *checkPerson = findCustomer(nameInput);
    if(checkPerson){
        printf("%s is present\n", nameInput);
    } else {
        printf("%s is not present\n", nameInput);
    }
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}

int viewWartegMenu(){
    viewPeople();
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}

int orderMenu(){
    char nameInput[255];
    do{
        printf("Insert the customer\'s name: ");
        scanf("%[^\n]", nameInput);
        getchar();
    } while (!checkName(nameInput));
    Person *currPerson = searchTable(nameInput);
    if(currPerson){
        order(currPerson);
    } else {
        printf("Person is not present \n");
    }
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}

int paymentMenu(){
    pay();
    printf("Press enter to continue...\n");
    getchar();  
    return 0;
}

int main(){
    int mainMenuCounter = 0;
    do{
        cls();
        switch(mainMenuCounter){
            case 0:
                mainMenuCounter = mainMenu();
                break;
            case 1:
                mainMenuCounter = addDishMenu();
                break;
            case 2:
                mainMenuCounter = removeDishMenu();
                break;
            case 3:
                mainMenuCounter = addCustomerMenu();
                break;
            case 4:
                mainMenuCounter = searchCustomerMenu();
                break;
            case 5:
                mainMenuCounter = viewWartegMenu();
                break;
            case 6:
                mainMenuCounter = orderMenu();
                break;
            case 7:
                mainMenuCounter = paymentMenu();
                break;
        }
    }while(mainMenuCounter != -1);
    FILE *fread = fopen("../FileRead/splash-screen.txt", "r");
    char close[255];
    while(fscanf(fread, "%[^\n]\n", close) != EOF){
        printf("%100s\n", close);
    }
    return 0;
}