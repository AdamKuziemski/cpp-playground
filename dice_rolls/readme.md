## Dice Rolls

I've created this project inspired by [this post](http://www.redblobgames.com/articles/probability/damage-rolls.html). My project lets you use any type of dice and then "cheat" with it. I imagine this could be useful if we wanted to increase the game difficulty by creating an AI that has better rolls on the same type of spell/weapon/etc, or by making the player's attacks or accuracy rolls worse.

### So now that we've got down the idea...

Let's get to the classes. The library provides five dice types:

* **Dice** is a basic class for every type of dice to inherit from. It provides basic functionality like generating pseudo-random numbers and performing rolls. It also provides two tool classes: **Range** - which is used for getting possible roll results - and **Iterator** - which can be used like any iterator from STL. The **Dice** class is designed to be abstract so it can't be instantiated.
* **SimpleDice** is a type of dice we normally encounter in games - the most common being `d6`, which is the standard dice everyone knows and also the default constructor for the class. RPG players also know `d4`, `d10`, `d12`, `d20` and so on. You can also provide a shift value so your rolls can reflect real RPG rolls like `3d6 + 10`.
* **UncappedDice** is a dice that can't be capped by result bounds. For example, a capped 2d6 + 4 roll won't go over 12, while an uncapped roll can.
* **RangedDice** rolls numbers from a given range, say, `[20, 30]` or `(12, 40]`. You can set it up to be left- or right- inclusive or exclusive if you like. It's both inclusive by default.
* **CustomValuedDice** will only return values from a given set of results, like `{4, 13, 16, 42, 96}`.

### And for the cheats...

There are a few different types of cheats you can use to load your dice. There's a basic cheat class called **DiceCheater** (duh) inheriting from **UncappedDice** that provides a base for every cheat. It contains a `shared_ptr` to the Dice you want to load. This means you can "stack" cheats on top of each other (like decorators) to achieve different distribution of possible results. Cool, huh?

* **HigherRollCheater** rolls a dice twice and returns the higher of results.
* **LowerRollCheater** rolls a dice twice and returns the lower of results.
* **CoinFlipCheater** rolls two dice and returns one of the results, based on a `rand() % 2` roll.
* **DoubleRollOnChance** rolls a dice and performs a percent-based probability check of a second roll, then returns the appropriate result.
* **DoubleValueOnChance** rolls a dice and performs a percent-based probability check of a double roll value, then returns the appropriate result.

### TODO

* **UniqueValueCheater** will roll a unique result every time, until it runs out of possible results (will reset itself)
* **DoubleRollIfHigherThan**
* **DoubleValueIfHigherThan**
* **DoubleRollIfLowerThan**
* **DoubleValueIfLowerThan**
