import java.util.ArrayList;
import java.util.List;

public abstract class T_AbstractTaskContainer implements Container {
    protected List<Task> tasks = new ArrayList<>();

    @Override
    public void add(Task task) {
        tasks.add(task);
    }

    @Override
    public int size() {
        return tasks.size();
    }

    @Override
    public boolean isEmpty() {
        return tasks.isEmpty();
    }

    @Override
    public abstract Task remove();
}
