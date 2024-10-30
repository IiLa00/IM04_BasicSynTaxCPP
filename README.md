# 설계.
## 어떤 작업을 해야할까?
    구현하기 전에 생각.
1. 프로젝트 세팅 
* 키보드 R - Reload 액션 이벤트
2. 재장전 몽타주 생성
* R키를 눌렀을 때 or 기존 탄알이 0발이 될 시, 
몽타주 재생 / 우클릭 입력(줌 인)과 1번(Equip) 입력 막기 / 줌 인 상태일 때 줌아웃으로 풀기.
* 몽타주 재생 중에 기존 탄창을 손에 집을 시, 
장탄 수 초기화 / 기존 탄창 떨어트리고 숨기기.
* 몽타주 재생 중에 손이 허리에 닿을 시,
탄창 스폰.
* 몽타주 재생 중에 스폰된 탄창 결합 시,
스폰된 탄창 삭제 / 기존 탄창 숨기기 풀기 / 총알 수 늘리기.
3. 총알 위젯 생성.

# 코드구현.
    구현하면서 작성.
1. 재장전 몽타주에 노티파이 스테이트 2개와 노티파이 1개를 심음.  
* 첫째 노티파이 스테이트(NotifyState_Reloading) 
  * Begin - 재장전 상태 돌입 / End - 재장전 상태 종료 및 몽타주 재생상태 종료.
    > 첫째 노티파이 스테이트는 굳이 노티파이 스테이트로 만들어야하나? 노티파이 2개로 퉁칠만큼 간단한데? <- 2개만들거 1개로 줄였으니 괜찮은건가?  

* 둘째 노티파이 스테이트(NotifyState_Magazine) 
  * Begin - 기존 탄창 숨기기 및 새 탄창 생성 및 피직스바디 부여(떨어트리기) / End - 기존 탄창 숨기기 풀고 새 탄창 Destroy 및 총알 수 늘리기.
* 노티파이(Notify_SpawnMagazine)
  * 새 탄창 스폰 및 손에 Attach.

2. 총알 위젯 (BulletWidget)
* 총을 들었을 때만 보이게 설정.
* BlueprintImplementableEvent를 이용해 함수 2개 구현, 인라인 함수로 함수 1개 구현.
  * 첫째 함수(Shooting)
     - CAR4->Firing_Internal() 에서 호출, 호출될 때마다 잔탄 수 감소.
  * 둘째 함수(Reloading)
     - 새 탄창 결합하는 노티파이스 스테이트에서 호출, 호출되면 잔탄 수 30으로 바뀜. 

# Detail
### About Montage
![image](https://github.com/user-attachments/assets/3a229de5-4925-4896-868c-3f85c138c38a)  
* NotifyState_Magazine의 Begin에서 생성한 탄창은 떨어트리는 탄창의 용도로 SetSpanLife를 1초로 둠으로써 1초뒤에 삭제,
  Notify_SpawnMagazine에서 스폰된 탄창이 NotifyState_Magazine의 End에서 삭제됨.


### About BulletWidget  
* 인터페이스에 `virtual UCBulletWidget* GetBulletWidget() = 0;` 추가.  
  * 총을 든 캐릭터는 누구나 가질 수 있게하기 위함.
* 잔탄 수가 0발이면 총알 위젯에서 bShoot변수를 false로 만듦, 이로인해 Player는 bShoot이 false면 재장전상태에 돌입하는 함수 실행.

# 코드후기
    뭔가 아쉽거나 이랬음 어땠을까? 하는 끄적끄적
현 코드는     
**총알위젯이 잔탄 수 상태를 관여해 잔탄 수가 0발이면 bShoot변수를 false로 설정함.   
그래서 CPlayer의 Tick에서 계속 총알위젯의 bShoot변수를 검사함, 만약 bShoot이 false면 재장전을 하기 위해.**   
> 원래는 잔탄 수 상태를 관리하는 클래스를 만드는 게 낫지않았나 싶었는데 굳이..? 만들지 않아도 관리할 수 있는데 새로 만들어야하나? 싶었음.
* * * 
> CPlayer의 Tick에서 계속 총알위젯의 bShoot변수를 검사하는게 아닌   잔탄 수가 0이면 Player의 어떤함수가 델리게이트로 만들었음 어떨까 싶었음, Tick으로 계속 검사하는게 비효율적이지 않나? 성능면에선 델리게이트가 훨 좋아보임.   
* * *
> ~~총알위젯이 CPlayer와 CAR4 두군데에서 사용되는데 한군데에서만 사용 가능하지않을까?~~ CAR4의 노티파이에 접근해야하고 CPlayer의 상태변경(줌아웃,몽타주 재생 시 다른행동 불가)의 이유로 두군데에서 사용해야한다고 판단함.

