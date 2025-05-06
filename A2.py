TABLE_SIZE = 10

class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashTable:
    def __init__(self):
        self.table = [None] * TABLE_SIZE

    def hash_function(self, key):
        return sum(ord(ch) for ch in key) % TABLE_SIZE

    def insert_without_replacement(self, key, value):
        idx = self.hash_function(key)
        new_node = Node(key, value)

        if self.table[idx] is None:
            self.table[idx] = new_node
        else:
            temp = self.table[idx]
            while temp.next:
                temp = temp.next
            temp.next = new_node

    def insert_with_replacement(self, key, value):
        idx = self.hash_function(key)
        new_node = Node(key, value)

        if self.table[idx] is None:
            self.table[idx] = new_node
        else:
            existing_idx = self.hash_function(self.table[idx].key)
            if existing_idx != idx:
                # Replace and reinsert the displaced node
                displaced = self.table[idx]
                self.table[idx] = new_node
                self.insert_without_replacement(displaced.key, displaced.value)
            else:
                # Same chain, append at end
                temp = self.table[idx]
                while temp.next:
                    temp = temp.next
                temp.next = new_node

    def find(self, key):
        idx = self.hash_function(key)
        temp = self.table[idx]

        while temp:
            if temp.key == key:
                print(f"Found Key: {key}, Value: {temp.value}")
                return
            temp = temp.next
        print(f"Key {key} not found.")

    def delete_key(self, key):
        idx = self.hash_function(key)
        temp = self.table[idx]
        prev = None

        while temp:
            if temp.key == key:
                if prev is None:
                    self.table[idx] = temp.next
                else:
                    prev.next = temp.next
                print(f"Key {key} deleted.")
                return
            prev = temp
            temp = temp.next
        print(f"Key {key} not found to delete.")

    def display(self):
        print("\nHash Table:")
        for i in range(TABLE_SIZE):
            print(f"{i}:", end=" ")
            temp = self.table[i]
            while temp:
                print(f"[{temp.key}, {temp.value}] ->", end=" ")
                temp = temp.next
            print("None")

# --- Main Program ---
def main():
    ht = HashTable()
    choice = int(input("Choose Collision Handling Method:\n1. Chaining Without Replacement\n2. Chaining With Replacement\nEnter choice: "))
    with_replacement = (choice == 2)

    while True:
        print("\n--- MENU ---")
        print("1. Insert (key, value)")
        print("2. Find key")
        print("3. Delete key")
        print("4. Display Table")
        print("5. Exit")

        ch = int(input("Enter your choice: "))
        if ch == 1:
            n = int(input("How many keys do you want to insert? "))
            for _ in range(n):
                key = input("Enter key: ")
                value = input("Enter value: ")
                if with_replacement:
                    ht.insert_with_replacement(key, value)
                else:
                    ht.insert_without_replacement(key, value)
        elif ch == 2:
            key = input("Enter key to find: ")
            ht.find(key)
        elif ch == 3:
            key = input("Enter key to delete: ")
            ht.delete_key(key)
        elif ch == 4:
            ht.display()
        elif ch == 5:
            break
        else:
            print("Invalid choice!")

if __name__ == "__main__":
    main()
