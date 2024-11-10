# Tamagotchi Embedded System Simulation

![image](https://github.com/user-attachments/assets/4229fb0e-b02a-4df3-9258-8afd37c5f820)

## Overview

This project, developed for the *Computer Architectures* course at Politecnico di Torino, involves creating a virtual Tamagotchi game using an ARM-based board (LANDTIGER) and the Keil µVision emulator. The objective is to implement and simulate the behavior of a Tamagotchi, a virtual pet that requires attention to stay alive. This project involves the development of the pet's logic, the interaction interface, animations, sound effects, and the integration of input/output peripherals, as well as the use of advanced programming techniques in C and assembly.

## Project Objectives

The goal of the project is to implement the key functionalities of a Tamagotchi game, including the management of its happiness, satiety, and age, by using various features of an ARM-based system:

- **Processor Structure & Memory Organization**: Understanding and programming the underlying hardware.
- **Input/Output Management**: Using peripherals like LEDs, buttons, potentiometers, speakers, and a display.
- **Firmware Development**: Writing in C and assembly language to interact with hardware components.
- **Keil Debug Environment**: Emulating and debugging the LPC1768 microcontroller using the LANDTIGER emulator (or actual hardware if available).

## Specifications

### Display and Animation
- **Tamagotchi Display**: The Tamagotchi should be shown in the middle of the LCD screen. The display updates every second with basic animations. You are encouraged to be creative with the Tamagotchi's design.
- **Animation**: An animation is required to make the Tamagotchi appear "alive". The animation will refresh every 1 second, and can be simple due to performance constraints.

### Tamagotchi Logic
- **Status Information**: Display the Tamagotchi's status at the top of the screen, including:
  - Age (in hours:minutes:seconds)
  - Happiness (on a scale of your choice)
  - Satiety (on a scale of your choice)
- **Food Menu**: A menu at the bottom of the screen, with options to feed the Tamagotchi. The user can select:
  - **Meal**: Increases satiety
  - **Snack**: Increases happiness
- **Food Animation**: When selecting a food option, an animation occurs showing the Tamagotchi moving toward the food and eating. The animation lasts at least 1 second.

### Tamagotchi Maintenance
- **Decrease in Happiness and Satiety**: Both happiness and satiety decrease over time (every 5 seconds by one bar).
- **Runaway Sequence**: If happiness or satiety reaches zero, the Tamagotchi "runs away". This triggers an animation where the Tamagotchi leaves the screen, and a message or icon will indicate its departure.
- **Reset Functionality**: After the Tamagotchi leaves, a reset button allows the player to start a new game with a new Tamagotchi, resetting its age, happiness, and satiety.

### Advanced Features
- **Touchscreen Interaction**: When the player touches the Tamagotchi on the touchscreen, an animation plays for 2 seconds. This increases the Tamagotchi's happiness by one bar.
- **Sound Effects**: Sound effects are included for key events:
  - Meal/Snack selection
  - Eating animation
  - Tamagotchi running away
  - Cuddles animation
- **Volume Control**: The volume of the sound effects can be adjusted using a potentiometer, sampled every 50 ms. The system should display a volume icon with the current volume level.

## Requirements

1. **Tamagotchi Display & Animation**:
   - Create a display that shows the Tamagotchi and updates with a simple animation every second.
   - Display the Tamagotchi's age, happiness, and satiety on the screen.
   - The food menu at the bottom should be visible with options for meal and snack.

2. **Virtual Pet Logic**:
   - Implement the logic for updating happiness, satiety, and age.
   - Trigger the runaway sequence when happiness or satiety reaches zero.
   - Implement a reset function to allow the player to start a new game.

3. **Touchscreen Interaction**:
   - Implement the cuddling feature, where touching the Tamagotchi increases happiness.
   - Ensure that the food menu, age, and status information cannot trigger animations.

4. **Sound Effects & Volume Control**:
   - Add sound effects for interactions with the food menu, eating animations, runaway sequence, and cuddles.
   - Implement volume control using a potentiometer to adjust the sound levels.

