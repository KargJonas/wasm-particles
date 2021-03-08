# Initial measurements
The measurements taken are highly dependent on the computer hardware they were taken on. This, however, will not be of great significance for the purpose of comparing JavaScript versus WebAssembly Performance, since all tests were performed on the same system.

System Specifications:
Operating system: Arch Linux x86 64-bit (Kernel version 5.9.13)
Memory: 16GB
Chrome Version: Google Chrome 87.0.4280.88 (Official Build) (64-bit)
Firefox Version: 83.0 (64-bit)

All measurements were taken on unaltered versions of Google Chrome and Mozilla Firefox, without any plugins of similar software installed. The testing conditions fore all tests were the same.

At a particle count of 2000, the unoptimized implementation of the system required approximately 89 milliseconds per step on Google Chrome and 141 ms/step on Mozilla Firefox.

The optimized verson performed about four times better at 20 ms/step on both Chrome and Firefox.

Interestingly, the pure JavaScript implementation performed *better* than both of the WebAssemply implementations at 13.4 ms/step on Chrome and 40 ms/step on Firefox.

These results are contradictary to the expected outcome, since the main premise of WebAssembly is that it's supposedly faster than JavaScript. In an effort to find a reason for the results I obtained, I made some investigations into what migh be the culprit.

[...]

An interesting observation I made whilst obtaining the measurements, was that the WebAssembly performance on Google Chrome drastically worsened upon opening the Chrome Developer Tools. When opening the developer tools panel, the time per step of the unoptimized version increased from 90 ms/step to approximately 211 ms/step (+134.4%). Upon cloasing the panel, the ms/step value returned to 90.

The amount of diifferent environments and implementations have forced me to make some decisions regarding the testing parameters. In order to make testing possible, I decided to test the performance optimized WebAssembly- versus the pure the JavaScipt implementation. Since Google Chrome has a larger market share (!!!)
