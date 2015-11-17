#include <stdio.h>
#include <string.h> /* memset */
#include "recipes_object.h"

// Define recipe information
#define RECIPE_TOTAL_LENGTH 112
#define RECIPE_NAME_LENGTH 16
#define RECIPE_AMOUNT_LENGTH 3
#define NUMBER_OF_RECIPES 5

Recipes recipes[NUMBER_OF_RECIPES];		// 5 Recipes structures

/* Struct for holding information about a particular recipe */
struct recipes {
	char RecipeName[RECIPE_NAME_LENGTH];
	char IngredientOne[RECIPE_NAME_LENGTH];
	char IngredientOne_amount[RECIPE_AMOUNT_LENGTH];
	float AmountOne;
	char IngredientTwo[RECIPE_NAME_LENGTH];
	char IngredientTwo_amount[RECIPE_AMOUNT_LENGTH];
	float AmountTwo;
	char IngredientThree[RECIPE_NAME_LENGTH];
	char IngredientThree_amount[RECIPE_AMOUNT_LENGTH];
	float AmountThree;
	char IngredientFour[RECIPE_NAME_LENGTH];
	char IngredientFour_amount[RECIPE_AMOUNT_LENGTH];
	float AmountFour;
	char GlassType[RECIPE_NAME_LENGTH];
};

/* Creates a new recipe struct */
Recipes newRecipes(){
	Recipes recipe=(Recipes)malloc(sizeof(struct recipes));
	memset(recipe, 0, sizeof(struct recipes));
	return recipe;
}

/* Prints out all info about recipe */
void dumpRecipeState(Recipes recipe){
	if(recipe==NULL) return;
	printf("Recipe name: %s\n", recipe->RecipeName);
	printf("Ingredient One: %s\n", recipe->IngredientOne);
	printf("Ingredient One Amount: %f\n", recipe->AmountOne);
	printf("Ingredient Two: %s\n", recipe->IngredientTwo);
	printf("Ingredient Two Amount: %f\n", recipe->AmountTwo);
	printf("Ingredient Three: %s\n", recipe->IngredientThree);
	printf("Ingredient Three Amount: %f\n", recipe->AmountThree);
	printf("Ingredient Four: %s\n", recipe->IngredientFour);
	printf("Ingredient Four Amount: %f\n", recipe->AmountFour);
	printf("Glass Type: %s\n", recipe->GlassType);
}

/* Frees memory allocated for recipe */
void deleteRecipe(Recipes recipe){
	free(recipe);
}

/* Set location of eeprom to look at for specific recipe */
int set_recipe_eeprom_address(int recipe_number) {
	int eeprom_memory_location = 0;
	switch(recipe_number) {
		case 0:
			return eeprom_memory_location;
		case 1:
			return eeprom_memory_location + RECIPE_TOTAL_LENGTH;
		case 2:
			return eeprom_memory_location + (RECIPE_TOTAL_LENGTH * 2);
		case 3:
			return eeprom_memory_location + (RECIPE_TOTAL_LENGTH * 3);
		case 4:
			return eeprom_memory_location + (RECIPE_TOTAL_LENGTH * 4);
		default:
			return eeprom_memory_location;
	}
}

/* Create structs for each recipe and fill them with eeprom data */
void init_recipes(void) {
	int i;
	for (i = 0; i < NUMBER_OF_RECIPES; i++) {
		recipes[i] = newRecipes();
		recipes[i] = get_recipe_from_eeprom(set_recipe_eeprom_address(i));
	}
	for(i = 0; i < NUMBER_OF_RECIPES; i++) {
		convert_amount_to_float(i);
	}
}

void convert_amount_to_float(int recipe) {
	recipes[recipe]->AmountOne = atof(recipes[recipe]->IngredientOne_amount);
	recipes[recipe]->AmountTwo = atof(recipes[recipe]->IngredientTwo_amount);
	recipes[recipe]->AmountThree = atof(recipes[recipe]->IngredientThree_amount);
	recipes[recipe]->AmountFour = atof(recipes[recipe]->IngredientFour_amount);
}

/* Read eeprom and save recipe information into struct */
Recipes get_recipe_from_eeprom(int location) {
	Recipes recipe;
	recipe = newRecipes();

	// Get recipe name from memory
    eeprom_read_block((void*)&recipe->RecipeName, (const void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Get ingredient one from memory
    eeprom_read_block((void*)&recipe->IngredientOne, (const void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Get ingredient one amount from memory
    eeprom_read_block((void*)&recipe->IngredientOne_amount, (const void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
    // Get ingredient two from memory
    eeprom_read_block((void*)&recipe->IngredientTwo, (const void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Get ingredient two amount from memory
    eeprom_read_block((void*)&recipe->IngredientTwo_amount, (const void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
    // Get ingredient three from memory
    eeprom_read_block((void*)&recipe->IngredientThree, (const void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Get ingredient three amount from memory
    eeprom_read_block((void*)&recipe->IngredientThree_amount, (const void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
	// Get ingredient four from memory
    eeprom_read_block((void*)&recipe->IngredientFour, (const void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Get ingredient four amount from memory
    eeprom_read_block((void*)&recipe->IngredientFour_amount, (const void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
	// Get glass type from memory
    eeprom_read_block((void*)&recipe->GlassType, (const void*)location, RECIPE_NAME_LENGTH);

    // Return recipe;
    return recipe;
}

/* TODO: change from eeprom_write to eeprom_update */
void save_recipe_to_eeprom(int recipe) {
	int location = set_recipe_eeprom_address(recipe);

	// Write ecipe name to memory
    eeprom_write_block ((void*)&recipes[recipe]->RecipeName, (void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Write ingredient one to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientOne, (void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;
    // Write ingredient one amount to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientOne_amount, (void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
    // Write ingredient two to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientTwo, (void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;    
    // Write ingredient two amount to memory to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientTwo_amount, (void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
    // Write ingredient three to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientThree, (void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;    
    // Write ingredient three amount to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientThree_amount, (void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
	// Write ingredient four to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientFour, (void*)location, RECIPE_NAME_LENGTH);
	location += RECIPE_NAME_LENGTH;    
    // Write ingredient four amount to memory
    eeprom_write_block ((void*)&recipes[recipe]->IngredientFour_amount, (void*)location, RECIPE_AMOUNT_LENGTH);
	location += RECIPE_AMOUNT_LENGTH+1;
	// Write glass type to memory
    eeprom_write_block ((void*)&recipes[recipe]->GlassType, (void*)location, RECIPE_NAME_LENGTH);
}

void manage_recipe(int recipe) {
	char choice;

	printf("\n--------------------\n");
	dumpRecipeState(recipes[recipe]);
	printf("\n--------------------\n");

	while (1) {
		printf("\n0. Display recipe's information\n");
		printf("1. Update recipe name\n");
		printf("2. Update ingredient one\n");
		printf("3. Update ingredient two\n");
		printf("4. Update ingredient three\n");
		printf("5. Update ingredient four\n");
		printf("6. Update glass type\n");
		printf("7. --POUR RECIPE--\n");
		printf("8. Back\n");
		printf("\nSelect an option (1-8): ");
		fgets(&choice, 1, stdin);

		if (choice == '0') {
			printf("\n--------------------\n");
			dumpRecipeState(recipes[recipe]);
			printf("\n--------------------\n");
		}
		else if (choice == '1') {
			update_recipe_name(recipe);
		}
		else if (choice == '2') {
			update_recipe_ingredient(recipe, 1);
		}
		else if (choice == '3') {
			update_recipe_ingredient(recipe, 2);
		}
		else if (choice == '4') {
			update_recipe_ingredient(recipe, 3);
		}
		else if (choice == '5') {
			update_recipe_ingredient(recipe, 4);
		}
		else if (choice == '6') {
			update_recipe_glass(recipe);
		}
		else if (choice == '7') {
			pour_recipe(recipe);
		}
		else if (choice == '8') {
			display_recipes();
		}
	}
}

void pour_recipe(int recipe) {
	int i;
	printf("\n----------\nPOURING RECIPE\n----------\n");
	printf("Make sure there is a glass ready\n\n");
	printf("Pouring in 5...");
	for (i = 4; i > 0; i--) {
		_delay_ms(500);
		printf("%d...", i);
	}
	printf("\n\nPouring %1.2f ounces of %s\n\n", recipes[recipe]->AmountOne, recipes[recipe]->IngredientOne);
	// Pour first ingredient
	pouring_length = (recipes[recipe]->AmountOne * OUNCE);
	begin_pouring(1);

	printf("Pouring %1.2f ounces of %s\n", recipes[recipe]->AmountTwo, recipes[recipe]->IngredientTwo);
	// Pour first ingredient
	pouring_length = (recipes[recipe]->AmountTwo * OUNCE);
	begin_pouring(2);

	printf("Pouring %1.2f ounces of %s\n", recipes[recipe]->AmountThree, recipes[recipe]->IngredientThree);
	// Pour first ingredient
	pouring_length = (recipes[recipe]->AmountThree * OUNCE);
	begin_pouring(3);
	
	printf("Pouring %1.2f ounces of %s\n", recipes[recipe]->AmountFour, recipes[recipe]->IngredientFour);
	// Pour first ingredient
	pouring_length = (recipes[recipe]->AmountFour * OUNCE);
	begin_pouring(4);
}

void update_recipe_name(int recipe) {
	printf("\n----------\nUpdate Recipe Name\n----------\n");
	char temp[USER_NAME_LENGTH];
	printf("Current name of the recipe: %s\n", recipes[recipe]->RecipeName);
	printf("New name of the recipe: ");
	fgets(temp, USER_NAME_LENGTH, stdin);
	memcpy(recipes[recipe]->RecipeName, clean_string(USER_NAME_LENGTH, temp), USER_NAME_LENGTH);

	save_recipe_to_eeprom(recipe);
	deleteRecipe(recipes[recipe]);
	recipes[recipe] = get_recipe_from_eeprom(set_recipe_eeprom_address(recipe));
	convert_amount_to_float(recipe);
	printf("\n--------------------\nRecipe updated\n--------------------\n");
	dumpRecipeState(recipes[recipe]);
}

void update_recipe_glass(int recipe) {
	printf("\n----------\nUpdate Glass Type\n----------\n");
	char temp[USER_NAME_LENGTH];
	printf("Current type of glass: %s\n", recipes[recipe]->GlassType);
	printf("New glass type: ");
	fgets(temp, USER_NAME_LENGTH, stdin);
	memcpy(recipes[recipe]->GlassType, clean_string(USER_NAME_LENGTH, temp), USER_NAME_LENGTH);
	// What happens to characters that are over length?

	save_recipe_to_eeprom(recipe);
	deleteRecipe(recipes[recipe]);
	recipes[recipe] = get_recipe_from_eeprom(set_recipe_eeprom_address(recipe));
	convert_amount_to_float(recipe);
	printf("\n--------------------\nRecipe updated\n--------------------\n");
	dumpRecipeState(recipes[recipe]);
}

void update_recipe_ingredient(int recipe, int ingredient) {
	printf("\n----------\nUpdate Recipe Ingredient\n----------\n");
	char temp_name[USER_NAME_LENGTH];
	char temp_amnt[USER_AMOUNT_LENGTH];

	printf("Enter the name of the ingredient: ");
	fgets(temp_name, USER_NAME_LENGTH, stdin);

	printf("Enter amount of ingredient (0-8 ounces): ");
	fgets(temp_amnt, USER_AMOUNT_LENGTH, stdin);


	if (ingredient == 1) {
		memcpy(recipes[recipe]->IngredientOne, clean_string(USER_NAME_LENGTH, temp_name), USER_NAME_LENGTH);
		memcpy(recipes[recipe]->IngredientOne_amount, clean_string(USER_AMOUNT_LENGTH, temp_amnt), USER_AMOUNT_LENGTH);
	}
	else if (ingredient == 2) {
		memcpy(recipes[recipe]->IngredientTwo, clean_string(USER_NAME_LENGTH, temp_name), USER_NAME_LENGTH);
		memcpy(recipes[recipe]->IngredientTwo_amount, clean_string(USER_AMOUNT_LENGTH, temp_amnt), USER_AMOUNT_LENGTH);
	}
	else if (ingredient == 3) {
		memcpy(recipes[recipe]->IngredientThree, clean_string(USER_NAME_LENGTH, temp_name), USER_NAME_LENGTH);
		memcpy(recipes[recipe]->IngredientThree_amount, clean_string(USER_AMOUNT_LENGTH, temp_amnt), USER_AMOUNT_LENGTH);
	}
	else if (ingredient == 4) {
		memcpy(recipes[recipe]->IngredientFour, clean_string(USER_NAME_LENGTH, temp_name), USER_NAME_LENGTH);
		memcpy(recipes[recipe]->IngredientFour_amount, clean_string(USER_AMOUNT_LENGTH, temp_amnt), USER_AMOUNT_LENGTH);
	}

	save_recipe_to_eeprom(recipe);
	deleteRecipe(recipes[recipe]);
	recipes[recipe] = get_recipe_from_eeprom(set_recipe_eeprom_address(recipe));
	convert_amount_to_float(recipe);
	printf("\n--------------------\nRecipe updated\n--------------------\n");
	dumpRecipeState(recipes[recipe]);
}