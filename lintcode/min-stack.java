// https://www.lintcode.com/problem/min-stack/description
// 37.40%, -

public class MinStack {

    private List<Integer> stack = new ArrayList<>();
    private List<Integer> mininumElements = new ArrayList<>();

    public MinStack() {
        // do intialization if necessary
    }

    /*
     * @param number: An integer
     * @return: nothing
     */
    public void push(int number) {
        stack.add(number);
        if (mininumElements.isEmpty()) {
            mininumElements.add(number);
        } else {
            if (number <= mininumElements.get(mininumElements.size() -1)) {
                mininumElements.add(number);
            }
        }
    }

    /*
     * @return: An integer
     */
    public int pop() {
        if (stack.size() == 0) {
            return -1;
        }
        int number = stack.remove(stack.size()-1);
        if (number == mininumElements.get(mininumElements.size() -1)) {
            mininumElements.remove(mininumElements.size() -1);
        }
        return number;
    }

    /*
     * @return: An integer
     */
    public int min() {
        if (mininumElements.isEmpty()) {
            return -1;
        }
        return mininumElements.get(mininumElements.size() -1);
    }
}
