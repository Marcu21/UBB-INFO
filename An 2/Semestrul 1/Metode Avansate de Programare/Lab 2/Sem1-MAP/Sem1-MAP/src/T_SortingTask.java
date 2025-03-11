import java.util.Arrays;

public class T_SortingTask extends Task {
    private int[] array;
    private T_AbstractSorter sorter;

    public T_SortingTask(String description, String id, int[] array, SortStrategy strategy) {
        super(description, id);
        this.array = array;
        switch (strategy) {
            case BUBBLE:
                this.sorter = new T_BubbleSort();
                break;
            case QUICK:
                this.sorter = new T_QuickSort();
                break;
        }
    }

    @Override
    public void execute() {
        sorter.sort(array);
        System.out.println(Arrays.toString(array));
    }
}
