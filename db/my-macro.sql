-- drop if exists and create table Units with an auto incrementing primary key id and a field name, 
DROP TABLE IF EXISTS Units;
CREATE TABLE Units (
    unit_id INTEGER PRIMARY KEY,
    name TEXT
);

INSERT INTO "Units" ("unit_id", "name") VALUES
('1', 'g'),
('2', 'kg'),
('3', 'litre'),
('4', 'ml'),
('5', 'tbsp'),
('6', 'tsp'),
('7', 'stick'),
('8', 'slice'),
('9', 'large'),
('10', 'small'),
('11', 'medium'),
('12', 'ounce'),
('13', 'crisps'),
('14', 'patty'),
('15', 'each'),
('16', 'cup'),
('17', 'oz');

-- drop if exists and create table Foods with primary key and fields id, name, fat, protein, carb, calories, nullable grams, nullable fluid ML
DROP TABLE IF EXISTS Foods;
CREATE TABLE Foods (
    food_id INTEGER PRIMARY KEY,
    name TEXT,
    fat INTEGER,
    protein INTEGER,
    carb INTEGER,
    calories INTEGER,
    quantity REAL,
    unit_id INTEGER,
    popularity INTEGER DEFAULT 0
);

-- insert data  id, name, fat, protein, carb, calories, quantity, unit_id
INSERT INTO Foods VALUES (1,'Hormel - Pepperoni Pizza 14 slices', 13, 5, 0, 140, 14, 8, 0);
INSERT INTO Foods VALUES (2,'Smuckers - Natural Crunchy Peanut Butter 16 g', 8, 4, 4, 95, 16, 1, 0);
INSERT INTO Foods VALUES (3,'Kirkland Mexican Shredded Cheese 1/3 cup', 9, 6, 1, 110, 0.33, 16, 0);
INSERT INTO Foods VALUES (4,'Kirkland - Thick sliced bacon 2 slices', 10, 10, 0, 140, 2, 8, 0);
INSERT INTO Foods VALUES (5,'Mozzarella 2 oz', 10, 10, 2, 140, 2, 12, 0);
INSERT INTO Foods VALUES (6,'Kerry gold butter - Butter 2 tbsp', 22, 0, 0, 200, 2, 5, 0);
INSERT INTO Foods VALUES (7,'EVOO 1 tbsp', 14, 0, 0, 120, 1, 5, 0);
INSERT INTO Foods VALUES (8,'Sour Cream 2 tbsp', 5, 1, 2, 60, 2, 5, 0);
INSERT INTO Foods VALUES (9,'Primal Kitchen - Pizza Sauce 1/4 cup', 5, 1, 2, 60, 0.25, 16, 0);
INSERT INTO Foods VALUES (10,'Cauliflower 100 g', 0, 2, 2, 24, 100, 1, 0);
INSERT INTO Foods VALUES (11,'Egg lg', 5, 6, 0, 70, 1, 9, 0);
INSERT INTO Foods VALUES (12,'Parmesean Reggiano 28 g', 8, 9, 1, 120, 28, 1, 0);
INSERT INTO Foods VALUES (13,'Goat Cheese 28 g', 6, 4, 2, 80, 28, 1, 0);
INSERT INTO Foods VALUES (14,'Chef John Pizza Crust 1 each', 28, 32, 36, 484, 1, 15, 0);
INSERT INTO Foods VALUES (15,'Cauliflower Head 1 each', 2, 16, 23, 15, 1, 15, 0);
INSERT INTO Foods VALUES (16,'Cream Cheese 1 oz', 10, 2, 2, 99, 1, 12, 0);
INSERT INTO Foods VALUES (17,'Almonds 1 cup', 69, 29, 13, 795, 1, 16, 0);
INSERT INTO Foods VALUES (18,'Monk Fruit Sweetener  cup', 0, 0, 0, 0, 1, 16, 0);
INSERT INTO Foods VALUES (19,'Regina Red Wine Vinegar 1 tbsp', 0, 0, 0, 0, 1, 5, 0);
INSERT INTO Foods VALUES (20,'Rebel Cookie Dough 1 cup', 30, 5, 1, 315, 1, 16, 0);
INSERT INTO Foods VALUES (21,'Kirkland Peanuts 1 tbsp', 5, 3, 2, 57, 1, 5, 0);
INSERT INTO Foods VALUES (22,'Lilys Chocolate Chips 30 chips (14g)', 4, 0, 0, 50, 14, 1, 0);
INSERT INTO Foods VALUES (23,'Readi Whip 5 g', 1, 0, 1, 15, 5, 1, 0);
INSERT INTO Foods VALUES (24,'Prairie Farm Heavy Cream 1 tbsp', 5, 0, 0, 45, 1, 5, 0);
INSERT INTO Foods VALUES (25,'Nutiva Mct 1 tbsp', 14, 0, 0, 130, 1, 5, 0);

-- drop table if exists and create table Recipes with primary key recipe_id, name, description, instructions, image
DROP TABLE IF EXISTS Recipes;
CREATE TABLE Recipes (
    recipe_id INTEGER PRIMARY KEY,
    name TEXT,
    description TEXT,
    instructions TEXT,
    url TEXT,
    servings INTEGER
);

-- insert data into Recipes id, name, description, instructions, url, servings
INSERT INTO Recipes VALUES (1, 'Pizza', 'Homemade Pizza', 'Combine as needed', "www.pizza.com", 4);
INSERT INTO Recipes VALUES (2, 'Cauliflower Pizza Crust', 'Homemade Crust', 'Chef John', "https://www.allrecipes.com/recipe/236600/chef-johns-cauliflower-pizza-crust/", 1);
INSERT INTO Recipes VALUES (3, 'Salad Dressing', 'Plain Salad Dressing', 'Shake until mixed', "www.evoo-recipes.com", 1);
INSERT INTO Recipes VALUES (4, 'Keto Cheesecake', 'Keto Cheesecake', 'Combine as needed', "www.ketocheesecake.com", 6);
INSERT INTO Recipes VALUES (5, 'Rebel Sunday', 'Custom', 'Combine as needed', "www.rebelcreamery.com", 1);
INSERT INTO Recipes VALUES (6, 'Coffee Mct Cream', 'Bullet Mct Cream', 'Combine as needed', "www.bulletcoffee.com", 1);

-- drop if table exists and create table xref_recipe_foods with primary key xref_id, recipe_id, food_id
DROP TABLE IF EXISTS xref_recipe_foods;
CREATE TABLE xref_recipe_foods (
    recipe_id INTEGER,
    food_id INTEGER,
    amount REAL,
    unit_id INTEGER
);

-- insert data into xref_recipe_foods - recipe_id, food_id, multiplier, unit_id
INSERT INTO xref_recipe_foods VALUES (1, 1, 1, 8);
INSERT INTO xref_recipe_foods VALUES (1, 5, 4, 12);
INSERT INTO xref_recipe_foods VALUES (1, 9, 1, 16);
INSERT INTO xref_recipe_foods VALUES (1, 3, 1, 16);
INSERT INTO xref_recipe_foods VALUES (1, 10, 1, 1);
INSERT INTO xref_recipe_foods VALUES (1, 11, 1, 9);
INSERT INTO xref_recipe_foods VALUES (2, 10, 1, 15);
INSERT INTO xref_recipe_foods VALUES (2, 11, 1, 9);
INSERT INTO xref_recipe_foods VALUES (2, 12, 1, 1);
INSERT INTO xref_recipe_foods VALUES (2, 13, 2, 12);
INSERT INTO xref_recipe_foods VALUES (3, 7, 2, 5);
INSERT INTO xref_recipe_foods VALUES (3, 19, 1, 5);
INSERT INTO xref_recipe_foods VALUES (4, 16, 16, 12);
INSERT INTO xref_recipe_foods VALUES (4, 17, 0.5, 16);
INSERT INTO xref_recipe_foods VALUES (4, 18, 1, 16);
INSERT INTO xref_recipe_foods VALUES (4, 11, 3, 9);
INSERT INTO xref_recipe_foods VALUES (5, 20, 0.5, 16);
INSERT INTO xref_recipe_foods VALUES (5, 21, 1, 5);
INSERT INTO xref_recipe_foods VALUES (5, 22, 1, 1);
INSERT INTO xref_recipe_foods VALUES (5, 23, 1, 1);
INSERT INTO xref_recipe_foods VALUES (6, 24, 1, 5);
INSERT INTO xref_recipe_foods VALUES (6, 25, 1, 5);

-- drop table if exists and create table daily_food with primary key int id, string name, string date, int dailyActivityBonusCalories
DROP TABLE IF EXISTS daily_food;
CREATE TABLE daily_food (
    id INTEGER PRIMARY KEY,
    date TEXT,
    exercise_calorie_bonus INTEGER
    weight REAL
);

INSERT INTO daily_food VALUES (1, '2023-05-12', 0, 223.5);
INSERT INTO daily_food VALUES (2, '2023-05-13', 0, 223.6);
INSERT INTO daily_food VALUES (3, '2023-05-22', 0, 218.2);
INSERT INTO daily_food VALUES (4, '2023-06-05', 0, 214.4);
INSERT INTO daily_food VALUES (5, '2023-06-08', 0, 213.8);
INSERT INTO daily_food VALUES (6, '2023-06-17', 0, 213.6);
INSERT INTO daily_food VALUES (7, '2023-06-21', 0, 212.6);
INSERT INTO daily_food VALUES (8, '2023-06-22', 0, 211.4);
INSERT INTO daily_food VALUES (9, '2023-06-23', 0, 210.6);
INSERT INTO daily_food VALUES (10, '2023-06-29', 0, 211.2);
INSERT INTO daily_food VALUES (11, '2023-06-30', 0, 209.4);
INSERT INTO daily_food VALUES (12, '2023-07-07', 0, 209.4);
INSERT INTO daily_food VALUES (13, '2023-07-08', 0, 208.2);
INSERT INTO daily_food VALUES (14, '2023-07-09', 0, 207.0);
INSERT INTO daily_food VALUES (15, '2023-07-13', 0, 206.8);
INSERT INTO daily_food VALUES (16, '2023-07-14', 0, 206.0);
INSERT INTO daily_food VALUES (17, '2023-07-15', 0, 205.0);
INSERT INTO daily_food VALUES (18, '2023-07-16', 0, 204.4);
INSERT INTO daily_food VALUES (19, '2023-07-24', 0, 205.8);
INSERT INTO daily_food VALUES (20, '2023-07-26', 0, 205.2);
INSERT INTO daily_food VALUES (21, '2023-07-27', 0, 205.2);
INSERT INTO daily_food VALUES (22, '2023-07-28', 0, 204.0);
INSERT INTO daily_food VALUES (23, '2023-08-02', 0, 202.8);
INSERT INTO daily_food VALUES (24, '2023-08-03', 0, 202.4);
INSERT INTO daily_food VALUES (25, '2023-08-04', 0, 200.4);
INSERT INTO daily_food VALUES (26, '2023-08-07', 0, 200.2);
INSERT INTO daily_food VALUES (27, '2023-08-08', 0, 200.8);

-- drop if table exists and create table xref_daily_food with primary key daily_food_id, food_id, multiplier
DROP TABLE IF EXISTS xref_daily_foods;
CREATE TABLE xref_daily_foods (
    id INTEGER PRIMARY KEY,
    daily_food_id INTEGER,
    name TEXT,
    fat INTEGER,
    protein INTEGER,
    carb INTEGER,
    calories INTEGER
);

-- insert data into xref_daily_food - daily_food_id, food_id, multiplier
INSERT INTO xref_daily_foods VALUES (1, 4, 'evoo oil 1 tsp (2)', 100, 0, 0, 900);
INSERT INTO xref_daily_foods VALUES (2, 4, 'goat cheese 28 g (1) ', 90, 0, 0, 800);
INSERT INTO xref_daily_foods VALUES (3, 4, 'Almonds 1 cup (0.2)', 303, 0, 0, 2727);
INSERT INTO xref_daily_foods VALUES (4, 4, 'Mozzarella 2 oz (3)', 56, 0, 0, 500);
INSERT INTO xref_daily_foods VALUES (5, 4, 'Cream Cheese 1 oz (1)', 44, 0, 0, 400);
INSERT INTO xref_daily_foods VALUES (6, 4, 'Kerry gold butter - Butter 2 tbsp (0.5)', 110, 0, 0, 1000);

-- drop if table exists and create table goal
DROP TABLE IF EXISTS goal;
CREATE TABLE goal (
    id INTEGER PRIMARY KEY,
    start_date TEXT,
    target_weight REAL,
    bmr_calories INTEGER,
    fat_percent INTEGER,
    protein_percent INTEGER,
    carb_percent INTEGER
);

INSERT INTO goal VALUES (1, '2023-05-31', 160, 1702, 75, 20, 5);
