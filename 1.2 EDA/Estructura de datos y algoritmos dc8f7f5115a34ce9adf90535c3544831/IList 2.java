package Laboratorio7;

/**
 * Lista de objetos de tipo String 
 * @author isegura
 *
 */
public interface IList {

	public void addFirst(String newElem);

	public void addLast(String newElem);

	public void removeFirst();

	public void removeLast();
	
	
	public void insertAt(int index, String newElem);
	
	public boolean isEmpty();

	public boolean contains(String elem);

	public int getSize();

	public int getIndexOf(String elem);

	public String getFirst();

	public String getLast();

	public String getAt(int index);
	
	public String toString();

	public void removeAll(String elem);

	public void removeAt(int index);

}


