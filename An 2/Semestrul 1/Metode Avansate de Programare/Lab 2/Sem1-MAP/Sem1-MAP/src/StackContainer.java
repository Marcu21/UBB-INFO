import java.util.ArrayList;
import java.util.List;

public class StackContainer extends T_AbstractTaskContainer {

    @Override
    public Task remove() {
        if (isEmpty()) {
            return null;
        }
        return tasks.remove(tasks.size() - 1);
    }
}
