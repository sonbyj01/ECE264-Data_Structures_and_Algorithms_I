def sort_names():
    f1 = open("firstNames.txt", "r")
    data_list1 = f1.readlines()
    f1.close()
    data_list1.sort()
    # for len(data_list1) - 'some value', use 7 for first name and 1 for last name
    for index in range(len(data_list1) - 7):
        if data_list1[index] == data_list1[index + 1]:
            data_list1.remove(data_list1[index])
    for index in range(len(data_list1)):
        data_list1[index] = "{{ \"{0}\", {1} }}, \n".format(data_list1[index].rstrip(), index)
    f2 = open("firstNamesSorted.txt", "w")
    f2.writelines(data_list1)

if __name__ == "__main__":
    sort_names()