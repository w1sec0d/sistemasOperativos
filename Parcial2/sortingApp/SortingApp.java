import java.util.concurrent.ForkJoinPool;


public class SortingApp {
    public static void main(String[] args) {
        int[] array = {34, 7, 23, 32, 5, 62, 31, 25, 12, 22, 11, 90};


        ForkJoinPool pool = new ForkJoinPool(); // Crear un pool de hilos


        // Usar Quicksort
        QuickSortTask quickSortTask = new QuickSortTask(array, 0, array.length - 1);
        pool.invoke(quickSortTask);


        // Usar Mergesort 
        // MergeSortTask mergeSortTask = new MergeSortTask(array, 0, array.length - 1);
        // pool.invoke(mergeSortTask);


        // Imprimir el array ordenado
        System.out.println("Array ordenado:");
        for (int num : array) {
            System.out.print(num + " ");
        }
    }
}
