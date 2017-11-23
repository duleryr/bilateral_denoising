%% Problem: finding neighborhood vertex of certain vertex
%
% Authors : Trung-Thien Tran
% Emal:       trung-thien.tran.1@ulaval.ca; 
%             tranthien9.vn@gmail.com
% Created : 06/12/2012
% From: 
% Copyright (c) 2014 CVSL Laboratory, Laval University, Canada
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
function  neigh_vertex=find_vertex_1neighbor(faces,i)

n=size(faces,1); % number of faces

%%
x=ceil(find(faces==i)/n);  % find column index
y=find(faces==i)-n*(x-1);   % find row index

%%
j=1:size(y,1);
O(j,:)=faces(y(j),:);   % faces include ith vertex
Order=unique(O);  % make it in order
neigh_vertex =Order(Order~=i)';  % output vertex
if size(neigh_vertex,1)>1
    neigh_vertex=neigh_vertex';
end
