# AdvProg_BTL
### Bùi Văn Hòa - 22021163
Bài tập lớn môn Lập trình nâng cao 

https://github.com/bufihofa/AdvProg_BTL/releases/tag/play ->  Tải file Play.zip -> nếu trình duyệt phát hiện virus -> giữ lại -> tải về -> giải nén -> mở file FireWizard.exe để chơi -> run anyway
# Endless Wizard
Mô tả game: Người chơi sẽ là một phù thủy, di chuyển để tránh né kẻ địch và nhặt các hạt kinh nghiệm để thăng cấp, thăng cấp sẽ được lựa chọn kỹ năng để thăng cấp, các kỹ năng sẽ tự động dùng lên các kẻ địch gần nhất sau mỗi khoảng trễ. Bản đồ vô hạn, số lượng và sức mạnh của kẻ địch tăng lên theo thời gian, kẻ địch có thể né các kỹ năng của bạn.
Có 3 chế độ: dễ, bình thường, khó. 
## Menu Game:
![MenuGame](https://i.ibb.co/7WV82QX/Untitled.png)

## Demo GamePlay
![GamePlay](https://i.ibb.co/x8Vn1zT/image.png)

## LevelUp Menu
![LevelUpMenu](https://i.ibb.co/zZhfGgx/Untitled.png)

## Pause Menu
![PauseMenu](https://i.ibb.co/CvwJ9zX/image.png)

## Dead Menu
![DeadMenu](https://i.ibb.co/rpn1qHq/image.png)


# Hệ thống Game:
## Gồm các Class:
![ClassList](https://i.ibb.co/wWxPRQ3/image.png)
## Class Game:
![Game](https://i.ibb.co/sPHchsr/image.png)
- Tất cả các lớp đều thông qua lớp này để xử lý sự kiện
## Class Animation:

![Animation](https://i.ibb.co/wNNfLhM/image.png)

- Sử dụng để lưu trữ các Ảnh có chung mục đích sử dụng, khi cần sử dụng ảnh chỉ cần trỏ đến địa chỉ có sẵn thay vì phải load ảnh mới từ file

## Class Animation List

![AnimationList](https://i.ibb.co/mH84XfV/image.png)
- Sử dụng để lưu lại các Animation và đặt tên cho chúng, các thao tác liên quan đến ảnh sẽ thông qua Class này để xử lý

## Class Point
![Point](https://i.ibb.co/dWPzNT6/image.png)
- Các thuộc tính X, Y, H, W có giá trị thực để xử lý Game dễ hơn

## Class Entity 
![Entity](https://i.ibb.co/bNsZPfy/image.png)
- Là lớp cơ sở để sử dụng SDL2, gồm các hàm để xử lý đồ họa
## Class NPC, Exp, Bullet, Player, Spike
![NPC](https://i.ibb.co/4ZVy0GD/image.png)
- Các lớp chính của Game, thông qua Game để xử lý

## Class Grid
![Grid](https://i.ibb.co/PjwwK7M/image.png)
- Sử dụng để xây dựng hướng di chuyển cho kẻ địch, chia màn hình thành lưới các ô vuông để xử lý

## Class Menu và Button
- Xử dụng để quản lý các GUI, Menu sẽ gồm các Button, nhận diện click, di chuyển chuột và bắt Button


## Bonus:
.![Bonus1](https://i.ibb.co/ZhjY0Zz/image.png)
.![Bonus2](https://i.ibb.co/vD66VV8/image.png)
