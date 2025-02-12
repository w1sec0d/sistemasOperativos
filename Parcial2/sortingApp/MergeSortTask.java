import java.util.concurrent.RecursiveAction;


public class MergeSortTask extends SortTask {
    private static final int THRESHOLD = 3; // Umbral para usar Insertion Sort en sublistas pequeñas


    // Constructor
    public MergeSortTask(int[] array, int start, int end) {
        super(array, start, end);
    }


    @Override
    protected void compute() {
        if (end - start <= THRESHOLD) {
            // Si la sublista es pequeña, usar Insertion Sort
            insertionSort(array, start, end);
        } else {
            int mid = (start + end) / 2; // Punto medio para dividir la lista


            // Crear tareas para las sublistas izquierda y derecha
            MergeSortTask leftTask = new MergeSortTask(array, start, mid);
            MergeSortTask rightTask = new MergeSortTask(array, mid + 1, end);


            // Ejecutar las tareas en paralelo
            invokeAll(leftTask, rightTask);


            // Fusionar las dos sublistas ordenadas
            merge(array, start, mid, end);
        }
    }


    // Insertion Sort para sublistas pequeñas
    private void insertionSort(int[] array, int start, int end) {
        for (int i = start + 1; i <= end; i++) {
            int key = array[i];
            int j = i - 1;
            while (j >= start && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }
}
