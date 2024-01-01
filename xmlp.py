import xml.etree.ElementTree as ET

def parse_xml(file_path):
    tree = ET.parse(file_path)
    root = tree.getroot()
    return root
"""
    # Access elements and attributes
    for element in root:
        print(element.tag, element.text)
        

    # Access element text
    for element in root.iter('tag_name'):
        print(element.text)
"""

"""
I am very well aware that all this could be a single function 
But one parameter here causes so many lines in c++ and we r running out of time
So these are tech debts we will never pay
"""

def get_character_atts(root):
    to_return = []
    for element in root:
        if element.tag == 'character':
            for child in element:
                print(child.tag, child.text)
                to_return.append(int(child.text))
    return to_return

def get_bouncing_atts(root):
    to_return = []
    for element in root:
        if element.tag == 'bouncing':
            for child in element:
                print(child.tag, child.text)
                to_return.append(int(child.text))
    return to_return

def get_boundary_atts(root):
    to_return = []
    for element in root:
        if element.tag == 'boundary':
            for child in element:
                print(child.tag, child.text)
                to_return.append(int(child.text))
    return to_return


print(get_bouncing_atts(parse_xml('map.xml')))
