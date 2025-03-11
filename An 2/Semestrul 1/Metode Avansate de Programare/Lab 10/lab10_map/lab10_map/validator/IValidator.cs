namespace lab10_map;

public interface IValidator<T>
{
    void Validate(T entity);
}
