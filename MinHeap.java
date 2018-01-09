import java.util.Arrays;
import java.util.Scanner;

/**
 * @author moonkyu77.kim
 *
 */
public class MinHeap {
	public static void main(String[] args) throws Exception {

		int i, input, inputCnt;
		System.setIn(new java.io.FileInputStream("heap_array_input.txt"));
		Scanner scan = new Scanner(System.in);
		MinHeap mh = new MinHeap();;
		
		inputCnt = scan.nextInt();
		
		for(i=0; i<inputCnt; i++) {
			input = scan.nextInt();
			if(input > 0) mh.push(input);
			else {
				if(mh.isEmpty()) System.out.println("0");
				else System.out.println(mh.pop());
			}
		}
		
	}

	private static final int MAX_HEAP_SIZE = 100005;
	
	public int mSize;
	public int[] mHeap;
	
	public MinHeap() {
		mSize = 0;
		mHeap = new int[MAX_HEAP_SIZE];
		Arrays.fill(mHeap, 0);
	}
	
	public boolean isEmpty() {
		if(mSize == 0) return true;
		else return false;
	}
	
	public void push (int _val) {
		int i = ++mSize;
		while (i != 1 && _val < mHeap[i/2]) {
			mHeap[i] = mHeap[i/2];
			i /= 2;
		}
		mHeap[i] = _val;
	}
	
	public int pop() {
		int item = mHeap[1];
		int temp = mHeap[mSize]; mHeap[mSize--] = 0;
		
		int parent = 1, child = 2;
		while(child <= mSize ) {
			if(mHeap[child]>0 && mHeap[child+1]>0 && mHeap[child] > mHeap[child+1]) {
				child = child+1;
			}
			if(mHeap[child] > temp) break;
			mHeap[parent] = mHeap[child];
			parent = child; child *= 2;
		}
		mHeap[parent] = temp;

		return item;
	}
}
