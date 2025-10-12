import random
from typing import List

class CommandGenerator:
    def __init__(self, min_val: int = -1000, max_val: int = 1000):
        self.min_val = min_val
        self.max_val = max_val
    
    def generate_command(self) -> str:
        if random.choice([True, False]):
            value = random.randint(self.min_val, self.max_val)
            return f"k {value}"
        else:
            value1 = random.randint(self.min_val, self.max_val)
            value2 = random.randint(self.min_val, self.max_val)
            return f"q {value1} {value2}"
    
    def generate_sequence(self, num_commands: int) -> List[str]:
        return [self.generate_command() for _ in range(num_commands)]
    
    def save_to_file(self, filename: str, num_commands: int):
        with open(filename, 'w', encoding='utf-8') as file:
            for _ in range(num_commands):
                file.write(self.generate_command() + '\n')

def main():
    generator = CommandGenerator()
    generator.save_to_file("./tests/e2e/test_data/5.dat", 100000)

if __name__ == "__main__":
    main()
