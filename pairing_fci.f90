program pairing_fci
  implicit none
  
  real(8),allocatable,dimension(:,:) :: Hamiltonian
  real(8),allocatable,dimension(:) :: eigs,work
  integer,allocatable,dimension(:,:) :: occupation_numbers
  integer :: i,j,q, num_pairs,num_levels,num_SD,lwork,info
  real(8) :: factorial,matrix_element ,delta,g,eref
  character(1) :: SDstr
  
  
  print*, 'DO NOT USE LARGE NUMBERS, IT WILL NOT WORK' 
  print*, 'how many energy levels?'
  read*, num_levels
  print*, 'single particle spacing? '
  read*, delta
!  print*, 'interaction strength? ' 
 ! read*, g 
  
  
  num_pairs = 2 
  
  ! get number of Slater determinants, this is where large numbers will fail. 

  num_SD = factorial(num_levels)/factorial(num_pairs)/factorial(num_levels-num_pairs) 
  allocate(Hamiltonian(num_SD,num_SD),occupation_numbers(num_SD,num_levels))
 
  
  ! table of pair occupation numbers for each SD
  occupation_numbers = 0
  
  q = 1
  do i = 1, num_levels
     do j = i+1,num_levels
        
        occupation_numbers(q,i) = 1
        occupation_numbers(q,j) = 1        
        q = q + 1
     end do
  end do 

   lwork = 10*num_SD
  allocate(eigs(num_SD),work(lwork)) 
  write(SDstr,'(I1)') num_SD
  
  
g = -1.d0
do while (g .le. 1.d0)
  ! set up hamiltonian 
  
  do i = 1, num_SD
     do j = i,num_SD 
        
        Hamiltonian(i,j) = matrix_element(  i, j , delta, g, &
             occupation_numbers ,num_SD,num_levels )  
        Hamiltonian(j,i) = Hamiltonian(i,j) !herm 
     end do 
  end do  

  eref = Hamiltonian(1,1) 
  ! diagonalize hamiltonian 
  
 
  call dsyev('V','U',num_SD,hamiltonian,num_SD,eigs,work,lwork,info)


  write(45,*) g, eigs(1) ,eref 

  g = g + .01 
end do 
  print*, 'fort.45 contains ground state and reference energy as a function of g' 
end program

real(8) function factorial(N) 
  ! don't use big numbers
  implicit none
  
  real(8) ::  x
  integer :: i
  integer,intent(in) :: N
  
  x = 1
  
  do i = 1,N
     x = x*i
  end do 
  
  factorial = x
  
end function

real(8) function matrix_element( SD1, SD2 , delta, g, occ,nSD,nlv ) 
  implicit none 
  
  integer :: SD1, SD2,nSD,nlv,i
  real(8) :: delta, g ,me
  integer,dimension(nSD,nlv) :: occ
  integer :: diff 
  
  diff = sum ( abs(occ(SD1,:) - occ(SD2,:)) ) 
  
  me = 0.d0
  if (diff == 0) then 
     
     ! this is the diagonal 
     
     do i = 1, nlv 
        me  = me +  2.d0 * delta * (i-1) * occ(SD1,i)

     end do
     me = me - g
  end if 
  
  if (diff == 2) then 
     
     ! one pair 
     me = -g/2.d0 
  end if 

  matrix_element = me

end function 

  
  

  
  
