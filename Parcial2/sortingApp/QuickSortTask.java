public class QuickSortTask extends SortTask {
    private static final int THRESHOLD = 100; // Umbral para usar Insertion Sort en sublistas pequeñas


    // Constructor
    public QuickSortTask(int[] array, int start, int end) {
        super(array, start, end);
    }


    @Override
    protected void compute() {
        if (end - start <= THRESHOLD) {
            // Si la sublista es pequeña, usar Insertion Sort
            insertionSort(array, start, end);
        } else {
            // Particionar la lista y obtener el índice del pivote
            int pivotIndex = partition(array, start, end);


            // Crear tareas para las sublistas izquierda y derecha
            QuickSortTask leftTask = new QuickSortTask(array, start, pivotIndex - 1);
            QuickSortTask rightTask = new QuickSortTask(array, pivotIndex + 1, end);


            // Ejecutar las tareas en paralelo
            invokeAll(leftTask, rightTask);
        }
    }


    // Método para particionar la lista
    private int partition(int[] array, int start, int end) {
        int pivot = array[end]; // Elegir el último elemento como pivote
        int i = start - 1; // Índice del elemento más pequeño


        for (int j = start; j < end; j++) {
            if (array[j] <= pivot) {
                i++;
                swap(array, i, j); // Intercambiar elementos
            }
        }
        swap(array, i + 1, end); // Colocar el pivote en su posición correcta
        return i + 1; // Retornar el índice del pivote
    }


    // Método para intercambiar dos elementos
    private void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
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
