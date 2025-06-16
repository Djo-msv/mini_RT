import random

# Define some constants
WIDTH = 20
HEIGHT = 10
BLOCK_SIZE = 5

class Block:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.type = random.choice(['stone', 'grass', 'dirt', 'water'])

    def draw(self):
        if self.type == 'stone':
            print('##', end=' ')
        elif self.type == 'grass':
            print('^^', end=' ')
        elif self.type == 'dirt':
            print('++', end=' ')
        elif self.type == 'water':
            print('~', end=' ')

    def interact(self):
        if self.type == 'water' and random.random() < 0.5:
            return 'You fell in the water!'
        else:
            return ''

class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move(self, dx, dy):
        self.x += dx
        self.y += dy

    def draw(self):
        print('P', end=' ')

# Create the game world
blocks = [[Block(x, y) for y in range(HEIGHT)] for x in range(WIDTH)]

# Create the player
player = Player(0, 0)

while True:
    # Clear the screen
    print('' * HEIGHT + '')

    # Draw the blocks
    for y in range(HEIGHT):
        for x in range(WIDTH):
            block = blocks[x][y]
            block.draw()
        print()

    # Draw the player
    player.draw()

    # Get user input
    command = input('Enter a command (w/a/s/d): ')

    if command == 'w':
        player.move(0, -1)
    elif command == 's':
        player.move(0, 1)
    elif command == 'a':
        player.move(-1, 0)
    elif command == 'd':
        player.move(1, 0)
