import csv

input_file = "data_8.csv"
output_file = "output_8.txt"
comp_count = 0
swap_count = 0

class Student:
    def __init__(self, student_id, name, score):
        self.student_id = student_id
        self.name = name
        self.score = score

def display_students(students):
    with open(output_file,"w") as file:
        for student in students:
            file.write(f"{student.student_id:4d},{student.name.ljust(16)},{student.score:3d}\n")

def read_student_data(filename):
    students = []
    with open(filename, newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            student_id, name, score = row
            students.append(Student(int(student_id), name.strip(), int(score)))
    return students

def quicksort(a:Student, left:int, right:int):
    global comp_count
    global swap_count
    if left < right:
        i, j = left, right
        x = a[(left + right) // 2]
        while True:
            while(a[i].score > x.score):
                i += 1
                comp_count += 1
            while(x.score > a[j].score):
                j -= 1
                comp_count += 1
            if (i <= j):
                if i < j:
                    a[i], a[j] = a[j], a[i]
                    swap_count += 1
                i += 1
                j -= 1
            if i > j: #調べる要素が残っていなければ終了
                break
        if left < j:
            quicksort(a, left, j)
        if i < right:
            quicksort(a , i, right)

def main():
    try:
        students = read_student_data(input_file)
        quicksort(students,0,len(students) - 1)
        display_students(students)
        print(f"比較回数 = {comp_count}，入れ換え回数 = {swap_count}")
        print(f"出力ファイル名: {output_file}")
    except FileNotFoundError:
        print("指定されたファイルが見つかりません。")

if __name__ == "__main__":
    main()
