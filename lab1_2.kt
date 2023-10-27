import java.util.Arrays

class Sorter {

    var intArray = arrayOf(40, 8, 11, 2, 9)

    fun swap(arr: IntArray, a: Int, b: Int) {
        val temp = arr[a]
        arr[a] = arr[b]
        arr[b] = temp
    }

    fun partition(arr: IntArray, low: Int, high: Int): Int {
        val pivot = arr[high]
        var i = low - 1

        for (j in low until high) {
            if (arr[j] < pivot) {
                i++
                swap(arr, i, j)
            }
        }

        swap(arr, i + 1, high)
        return i + 1
    }

    fun quickSort(arr: IntArray, low: Int, high: Int) {
        if (low < high) {
            val pi = partition(arr, low, high)

            quickSort(arr, low, pi - 1)
            quickSort(arr, pi + 1, high)
        }
    }

}

fun main() {
    val arr = intArrayOf(40, 8, 11, 2, 9)
    val sort = Sorter()

    sort.quickSort(arr,0, arr.size - 1)

    println(Arrays.toString(arr))
}