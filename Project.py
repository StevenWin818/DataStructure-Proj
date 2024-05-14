import os

# 定义一个节点类，用于存储学生的信息
class Node:
    def __init__(self, id=0, name='', gender='', temperature=0.0, hour=0, minute=0, next=None):
        self.id = id  # 学生的学号
        self.name = name  # 学生的姓名
        self.gender = gender  # 学生的性别
        self.temperature = temperature  # 学生的体温
        self.hour = hour  # 学生进入图书馆的时间（小时）
        self.minute = minute  # 学生进入图书馆的时间（分钟）
        self.next = next  # 指向下一个节点

# 定义一个链表类，用于存储和操作学生信息的节点
class LinkedList:
    def __init__(self):
        self.head = None  # 链表的头节点
        self.size = 0  # 链表的大小（节点的数量）

    # 添加一个新的学生信息节点
    def add(self):
        new_node = Node()
        new_node.id = int(input("请输入学号："))
        new_node.name = input("请输入姓名：")
        new_node.gender = input("请输入性别：")
        # 确保输入的体温在合理范围内
        while True:
            new_node.temperature = float(input("请输入体温："))
            if 35 <= new_node.temperature <= 42:
                break
            print("体温输入异常，请输入35-42之间的体温")
        # 确保输入的时间（小时）在合理范围内
        while True:
            new_node.hour = int(input("请输入进入图书馆的时间（时）："))
            if 0 <= new_node.hour <= 23:
                break
            print("时间（时）输入异常，请输入0-23之间的时间")
        # 确保输入的时间（分钟）在合理范围内
        while True:
            new_node.minute = int(input("请输入进入图书馆的时间（分）："))
            if 0 <= new_node.minute < 60:
                break
            print("时间（分）输入异常，请输入0-59之间的时间")
        # 将新节点添加到链表的头部
        new_node.next = self.head
        self.head = new_node
        self.size += 1

    # 打印链表中的所有学生信息
    def print(self):
        current = self.head
        while current is not None:
            print(f"学号：{current.id}")
            print(f"姓名：{current.name}")
            print(f"性别：{current.gender}")
            print(f"体温：{current.temperature}")
            print(f"进入图书馆的时间：{current.hour:02d}:{current.minute:02d}")
            print("--------------------")
            current = current.next

    # 对链表中的学生信息进行排序（按体温）
    def sort(self):
        if self.head is None:
            return
        self.head = self._merge_sort(self.head)

    # 使用归并排序算法对链表进行排序
    def _merge_sort(self, head):
        if head is None or head.next is None:
            return head
        mid = self._get_middle(head)
        mid_next = mid.next
        mid.next = None
        left = self._merge_sort(head)
        right = self._merge_sort(mid_next)
        return self._merge(left, right)

    # 合并两个排序好的链表
    def _merge(self, a, b):
        result = None
        if a is None:
            return b
        if b is None:
            return a
        if a.temperature >= b.temperature:
            result = a
            result.next = self._merge(a.next, b)
        else:
            result = b
            result.next = self._merge(a, b.next)
        return result

    # 获取链表的中间节点
    def _get_middle(self, head):
        if head is None:
            return head
        slow = head
        fast = head
        while fast.next is not None and fast.next.next is not None:
            slow = slow.next
            fast = fast.next.next
        return slow

    # 统计并打印体温高于或等于37度的学生信息
    def statistics(self):
        current = self.head
        count = 0
        print("体温高于或等于37度的学生信息如下：")
        while current is not None:
            if current.temperature >= 37.0:
                count += 1
                print(f"学号：{current.id}")
                print(f"姓名：{current.name}")
                print(f"性别：{current.gender}")
                print(f"体温：{current.temperature}")
                print(f"进入图书馆的时间：{current.hour:02d}:{current.minute:02d}")
                print("--------------------")
            current = current.next
        print(f"体温高于或等于37度的学生人数：{count}")

    # 将链表中的学生信息保存到文件中
    def save(self):
        with open("data.txt", "w") as file:
            current = self.head
            while current is not None:
                file.write(f"{current.id} {current.name} {current.gender} {current.temperature} {current.hour} {current.minute}\n")
                current = current.next

    # 从文件中加载学生信息，并添加到链表中
    def load(self):
        try:
            with open("data.txt", "r") as file:
                lines = file.readlines()
                for line in reversed(lines):
                    id, name, gender, temperature, hour, minute = line.strip().split()
                    new_node = Node(int(id), name, gender, float(temperature), int(hour), int(minute))
                    new_node.next = self.head
                    self.head = new_node
        except FileNotFoundError:
            pass

    # 根据学号或姓名查找学生信息
    def search(self, key):
        current = self.head
        while current is not None:
            if str(current.id) == key or current.name == key:
                print(f"找到学生信息如下：")
                print(f"学号：{current.id}")
                print(f"姓名：{current.name}")
                print(f"性别：{current.gender}")
                print(f"体温：{current.temperature}")
                print(f"进入图书馆的时间：{current.hour:02d}:{current.minute:02d}")
                return current
            current = current.next
        print(f"未找到学号或姓名为 {key} 的学生")
        return None

    # 根据学号或姓名删除学生信息
    def delete(self, key):
        student_to_delete = self.search(key)
        if student_to_delete is None:
            return
        confirm = input("是否要删除该学生信息？(y/n): ")
        if confirm.lower() == 'y':
            current = self.head
            prev = None
            while current != student_to_delete:
                prev = current
                current = current.next
            if prev is None:
                self.head = current.next
            else:
                prev.next = current.next
            self.size -= 1
            print("学生信息已删除")
        else:
            print("取消删除操作")

# 打印菜单
def menu():
    print("\n" + "="*30)
    print("图书馆人员管理系统".center(26))
    print("="*30)
    print("1. 添加学生信息")
    print("2. 按体温对学生排序")
    print("3. 对学生查找")
    print("4. 打印全部学生信息")
    print("5. 筛选体温高于37的学生")
    print("6. 删除指定学生")
    print("7. 退出程序")
    print("="*30 + "\n")
    
# 主函数，程序的入口
def main():
    list = LinkedList()
    list.load()
    while True:
        menu()
        choice = int(input("请输入你的选择："))
        if choice == 1:
            list.add()
        elif choice == 2:
            list.sort()
        elif choice == 3:
            key = input("请输入要查找的学生的学号或姓名：")
            list.search(key)
        elif choice == 4:
            list.print()
        elif choice == 5:
            list.statistics()
        elif choice == 6:
            key = input("请输入要删除的学生的学号或姓名：")
            list.delete(key)
        elif choice == 7:
            list.save()
            print("退出程序")
            break
        else:
            print("无效的选择，请重新输入")
        list.save()
        input("\n按回车键以继续...")
        os.system('cls')

# 如果这个.py文件是直接运行的，那么就执行main()函数
if __name__ == "__main__":
    main()