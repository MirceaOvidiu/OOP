class Student(
    private val firstName: String,
    private val lastName: String,
    private val birthYear: Int,
    private val CNP: String,
    private val faculty: String,
    private val facultyYear: Int
) {
    fun getFirstName(): String {
        return firstName
    }

    fun getLastName(): String {
        return lastName
    }

    fun getBirthYear(): Int {
        return birthYear
    }

    fun getFaculty(): String {
        return faculty
    }

    fun getFacultyYear(): Int {
        return facultyYear
    }

    fun calculateAge(): Int {
        return (2023 - getBirthYear())
    }

    fun genderByCNP(): String {
        return if (CNP[0] == '1' || CNP[0] == '5') {
            "male"
        } else if (CNP[0] == '2' || CNP[0] == '6') {
            "female"
        } else {
            "idk"
        }
    }

    fun yearGap(): Int {
        return (getBirthYear() - getFacultyYear())
    }
}

fun main() {
    val student1 = Student("Ion", "Popescu", 2000, "1930806378260", "ACS", 1967)
    val student2 = Student("Maria", "Popescu", 2001, "6931110326224", "ACS", 1967)

    println("the student is: ${student1.genderByCNP()}, ${student1.calculateAge()} years of age, studying at ${student1.getFaculty()} ${student1.yearGap()}, years older")
    println("the student is: ${student2.genderByCNP()}, ${student2.calculateAge()} years of age, studying at ${student2.getFaculty()} ${student2.yearGap()}, years older")
}


