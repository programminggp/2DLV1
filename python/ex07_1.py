import csv

class Student:
    def __init__(self, student_id, name, score):
        self.student_id = student_id
        self.name = name
        self.score = score

def display_students(students):
    print("学籍番号, 氏名           , 得点")
    for student in students:
        print(f"{student.student_id:4d},{student.name.ljust(16)},{student.score:3d}")

def read_student_data(filename):
    students = []
    with open(filename, newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            student_id, name, score = row
            students.append(Student(int(student_id), name.strip(), int(score)))
    return students

def quick_sort(students):
    left = []
    middle = []
    right = []
    if len(students) <= 1:
        return students
    ref = students[0].score
    for ele in students:
        if ele.score > ref:
           left.append(ele)
        elif ele.score < ref:
            right.append(ele)
        else:
            middle.append(ele)
    left = quick_sort(left)
    right = quick_sort(right)
    return left + middle + right


def main():
    filename = input("ファイル名を入力してください: ")
    try:
        students = read_student_data(filename)
        students = quick_sort(students)
        display_students(students)
    except FileNotFoundError:
        print("指定されたファイルが見つかりません。")

if __name__ == "__main__":
    main()
