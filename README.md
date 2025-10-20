# DSA-Analysis-and-Design

Course Planner Project Reflection

As a computer science student, my journey through this project has been both challenging and enlightening. When I first approached the task of creating a course planning system, I found myself facing a crucial decision that every software developer encounters: choosing the right data structure for the job.

Initially, I explored three different approaches. My first attempt used a simple vector implementation - it seemed straightforward enough, but I quickly discovered its limitations. While testing with a small dataset worked fine, I realized that checking for duplicate courses meant comparing each new course against every existing one, leading to an O(n²) runtime that would become painfully slow with a real course catalog.

This realization led me to explore more efficient solutions. I investigated a binary search tree approach, which offered better performance with O(n log n) runtime, but something still didn't feel quite right. It was during this exploration that I had my "aha" moment - course numbers are perfect hash keys! This insight led me to implement a hash table solution, which transformed our lookup times to O(1).

The development process wasn't without its challenges. I struggled particularly with handling collisions in the hash table and ensuring prerequisites were valid. I overcame these obstacles by implementing a chaining system using linked lists and developing a two-pass validation system. The first pass collects valid course numbers, while the second creates the actual course entries - it's not the most intuitive solution, but it works beautifully.

What really surprised me was how this project changed my approach to software development. I used to dive straight into coding, but now I find myself spending more time on design and analysis. I've learned to think critically about efficiency and maintainability. The code I wrote at the end of the project looks vastly different from what I might have written at the beginning - it's more modular, better documented, and more robust in handling edge cases.

Most importantly, this project taught me that there's rarely a perfect solution in software development - it's all about trade-offs. While my hash table implementation requires more complex code than a simple vector would, its performance benefits make it the right choice for this specific application. As I look back, I can see how much this project has helped me grow from someone who just writes code into someone who engineers solutions.

This experience has fundamentally changed how I approach programming problems. Now, before writing a single line of code, I find myself analyzing the problem space, considering different data structures, and thinking about long-term maintainability. It's no longer just about making something work - it's about making it work well, both now and in the future.
