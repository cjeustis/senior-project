#ifndef RECIPES_OBJECT_H
#define RECIPES_OBJECT_H

typedef struct recipes * Recipes;
Recipes newRecipes();
int dumpRecipeState(Recipes);
int deleteRecipe(Recipes);
void convert_amount_to_float(int recipe);
int set_recipe_eeprom_address(int recipe_number);
void init_recipes(void);
Recipes get_recipe_from_eeprom(int location);
void save_recipe_to_eeprom(int recipe);
int update_recipe_name(int recipe);
int update_recipe_glass(int recipe);
int update_recipe_ingredient(int recipe, int ingredient);

#endif