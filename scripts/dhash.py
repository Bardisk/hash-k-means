from PIL import Image, ImageOps
import sys
import imagehash

img_name = 'img.jpg'
if len(sys.argv) > 1:
  img_name = sys.argv[1]

img = Image.open(img_name)

# is there alpha channel?
if img.mode in ('RGBA', 'LA') or (img.mode == 'P' and 'transparency' in img.info):
  if img.mode == 'P':
    img = img.convert('RGBA')
  if img.mode == 'LA':
    img = img.convert('RGBA')
    
  # average grayscale in the image
  grayscale = img.convert('L')
  avg_gray = int(sum(grayscale.getdata()) / len(grayscale.getdata()))

  data = img.load()

  # set white or black for transparent pixels
  for i in range(img.size[0]):
    for j in range(img.size[1]):
      if data[i, j][3] < 32:
        data[i, j] = (255 - avg_gray, 255 - avg_gray, 255 - avg_gray, 255)
      else:
        data[i, j] = (data[i, j][0], data[i, j][1], data[i, j][2], 255)

  img = img.convert('RGB')
  # img.save("new_" + img_name)
else:
  img = img.convert('RGB')
  # img.save("new_" + img_name)

print(imagehash.dhash(img))