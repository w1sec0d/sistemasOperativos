import java.util.concurrent.RecursiveAction;


public abstract class SortTask extends RecursiveAction {
    protected final int[] array; // Array a ordenar
    protected final int start;  // Índice de inicio de la sublista
    protected final int end;    // Índice de fin de la sublista


    // Constructor
    public SortTask(int[] array, int start, int end) {
        this.array = array;
        this.start = start;
        this.end = end;
    }


    // Método para fusionar dos sublistas ordenadas
    protected void merge(int[] array, int start, int mid, int end) {
        int[] temp = new int[end - start + 1]; // Array temporal para almacenar la fusión
        int i = start, j = mid + 1, k = 0;


        // Fusionar las dos sublistas ordenadas
        while (i <= mid && j <= end) {
            if (array[i] <= array[j]) {
                temp[k++] = array[i++];
            } else {
                temp[k++] = array[j++];
            }
        }


        // Copiar los elementos restantes de la primera sublista
        while (i <= mid) {
            temp[k++] = array[i++];
        }


        // Copiar los elementos restantes de la segunda sublista
        while (j <= end) {
            temp[k++] = array[j++];
        }


        // Copiar el array temporal al array original
        System.arraycopy(temp, 0, array, start, temp.length);
    }
}
