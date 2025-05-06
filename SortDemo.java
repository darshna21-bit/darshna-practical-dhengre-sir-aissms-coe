import java.util.*;

public class SortDemo {
    
    // Heap Sort
    public static void heapSort(int[] a) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(a, n, i);
        for (int i = n - 1; i >= 0; i--) {
            int temp = a[0];
            a[0] = a[i];
            a[i] = temp;
            heapify(a, i, 0);
        }
    }

    public static void heapify(int[] a, int n, int i) {
        int large = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < n && a[left] > a[large]) large = left;
        if (right < n && a[right] > a[large]) large = right;
        if (large != i) {
            int temp = a[i];
            a[i] = a[large];
            a[large] = temp;
            heapify(a, n, large);
        }
    }

    // Shell Sort
    public static void shellSort(int[] a) {
        int n = a.length;
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = a[i], j = i;
                while (j >= gap && a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                a[j] = temp;
            }
        }
    }

    // Main Function
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();
        int[] arr = new int[n];
        System.out.println("Enter elements:");
        for (int i = 0; i < n; i++) arr[i] = sc.nextInt();

        System.out.println("Choose Sorting Method:");
        System.out.println("1. Heap Sort");
        System.out.println("2. Shell Sort");
        int choice = sc.nextInt();

        if (choice == 1) heapSort(arr);
        else if (choice == 2) shellSort(arr);
        else {
            System.out.println("Invalid choice!");
            return;
        }

        System.out.println("Sorted Array:");
        for (int x : arr) System.out.print(x + " ");
    }
}