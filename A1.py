TABLE_SIZE = 10

class Client:
    def __init__(self, name, phone_number):
        self.name = name
        self.phone_number = phone_number

class HashTableLinear:
    def __init__(self):
        self.table = [None] * TABLE_SIZE

    def hash_function(self, key):
        return sum(ord(c) for c in key) % TABLE_SIZE

    def insert(self, name, phone_number):
        index = self.hash_function(name)
        original_index = index

        while self.table[index] is not None:
            index = (index + 1) % TABLE_SIZE
            if index == original_index:
                print("Hash Table is full!")
                return

        self.table[index] = Client(name, phone_number)

    def search(self, name):
        comparisons = 0
        index = self.hash_function(name)
        original_index = index

        while self.table[index] is not None:
            comparisons += 1
            if self.table[index].name == name:
                print(f"Found {name}: {self.table[index].phone_number}")
                return comparisons
            index = (index + 1) % TABLE_SIZE
            if index == original_index:
                break

        print(f"{name} not found.")
        return comparisons

class HashTableQuadratic:
    def __init__(self):
        self.table = [None] * TABLE_SIZE

    def hash_function(self, key):
        return sum(ord(c) for c in key) % TABLE_SIZE

    def insert(self, name, phone_number):
        index = self.hash_function(name)
        i = 0

        while self.table[(index + i * i) % TABLE_SIZE] is not None:
            i += 1
            if i == TABLE_SIZE:
                print("Hash Table is full!")
                return

        self.table[(index + i * i) % TABLE_SIZE] = Client(name, phone_number)

    def search(self, name):
        comparisons = 0
        index = self.hash_function(name)
        i = 0

        while self.table[(index + i * i) % TABLE_SIZE] is not None:
            comparisons += 1
            if self.table[(index + i * i) % TABLE_SIZE].name == name:
                print(f"Found {name}: {self.table[(index + i * i) % TABLE_SIZE].phone_number}")
                return comparisons
            i += 1
            if i == TABLE_SIZE:
                break

        print(f"{name} not found.")
        return comparisons

# Main program
def main():
    linear = HashTableLinear()
    quadratic = HashTableQuadratic()

    n = int(input("How many clients you want to insert? "))
    for _ in range(n):
        name = input("Enter name: ")
        phone = input("Enter phone number: ")

        linear.insert(name, phone)
        quadratic.insert(name, phone)

    search_name = input("\nEnter name to search: ")

    print("\n--- Linear Probing ---")
    comp_linear = linear.search(search_name)

    print("\n--- Quadratic Probing ---")
    comp_quadratic = quadratic.search(search_name)

    print("\nComparisons:")
    print(f"Linear Probing: {comp_linear}")
    print(f"Quadratic Probing: {comp_quadratic}")

if __name__ == "__main__":
    main()
