import csv

class Player:
    def __init__(self, num, name, prof):
        self.num = num
        self.name = name
        self.prof = prof
        self.left = None
        self.right = None
    
class SearchTree:
    def __init__(self):
        self.root = None

    def add(self, player):
        if self.root is None:
            self.root = player
        else:
            self._add(self.root, player)

    def _add(self, node, player):
        if player.num < node.num:
            if node.left is None:
                node.left = player
            else:
                self._add(node.left,player)
        else:
            if node.right is None:
                node.right = player
            else:
                self._add(node.right, player)

#    def display_players(self, players):
#        for player in players:
#            self.display_player(player)

    def display_player(self, player):
        print(f"{player.num:4d},{player.name.ljust(16)},{player.prof}")

    def display_right(self, node):
        if node.right is not None:
            self.display_right(node.right)
        self.display_player(node)
        if node.left is not None:
            self.display_right(node.left)

    def display(self):
        if self.root is not None:
            self.display_right(self.root)


def display_players(players):
    for player in players:
        display_player(player)

def display_player(player):
    print(f"{player.num:4d},{player.name.ljust(16)},{player.prof}")
    

def read_player_data(filename):
    players = []
    with open(filename, newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile, delimiter=' ')
        for row in reader:
            num, name, prof = row
            players.append(Player(int(num), name.strip(), prof))
    return players


def main():
#    filename = input("ファイル名を入力してください: ")
    filename = "Zac_Japan.txt"
    try:
        players = read_player_data(filename)
        st = SearchTree()
        print("")
        for player in players:
            st.add(player)
        st.display()
        
    except FileNotFoundError:
        print("指定されたファイルが見つかりません。")

if __name__ == "__main__":
    main()
