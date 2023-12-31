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
def get_character_atts(root):
    to_return = []
    for element in root:
        if element.tag == 'character':
            for child in element:
                print(child.tag, child.text)
                to_return.append(child.text)
    return to_return

def get_bouncing_atts(root):
    to_return = []
    for element in root:
        if element.tag == 'bouncing':
            for child in element:
                print(child.tag, child.text)
                to_return.append(child.text)
    return to_return
# 

print(get_bouncing_atts(parse_xml('map.xml')))
