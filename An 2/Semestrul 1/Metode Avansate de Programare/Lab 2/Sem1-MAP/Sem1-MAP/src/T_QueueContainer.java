import java.util.ArrayList;
import java.util.List;

public class T_QueueContainer extends T_AbstractTaskContainer {
    @Override
    public Task remove() {
        if (isEmpty()) {
            return null;
        }
        return tasks.remove(0);
    }
}
