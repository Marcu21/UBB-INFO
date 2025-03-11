using lab10_map.domain;

namespace lab10_map.repository;


public delegate E StringToEntity<E>(string input);
public delegate string EntityToString<E>(E entity);

public class FileRepository<E,ID>: InMemoryRepository<E,ID> where E : Entity<ID>
{
    private string FilePath;
    private StringToEntity<E> StringToEntity;
    private EntityToString<E> EntityToString;

    public FileRepository(string filePath, StringToEntity<E> stringToEntity, EntityToString<E> entityToString)
    {
        FilePath = filePath;
        StringToEntity = stringToEntity;
        EntityToString = entityToString;
        ReadFromFile();
    }

    public void ReadFromFile()
    {
        using (StreamReader sr = new StreamReader(FilePath))
        {
            string line;
            while ((line=sr.ReadLine())!=null)
                base.Save(StringToEntity(line));
        }
    }

    public void WriteToFile()
    {
        using (StreamWriter sw = new StreamWriter(FilePath))
            foreach (E entity in base.FindAll())
                sw.WriteLine(EntityToString(entity));
    }

    public override E? Save(E entity)
    {
        E? e= base.Save(entity);
        if(e != null)
            WriteToFile();
        return e;
    }

    public override E? Update(E entity)
    {
        E? e = base.Update(entity);
        if(e != null)
            WriteToFile();
        return e;
    }

    public override E? Delete(ID id)
    {
        E? e = base.Delete(id);
        if(e!=null)
            WriteToFile();
        return e;
    }
}